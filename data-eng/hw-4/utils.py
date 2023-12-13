from lxml import etree
from bs4 import BeautifulSoup
from copy import deepcopy

def get_root(xml_file_path):
    tree = etree.parse(xml_file_path)
    return tree.getroot()

def get_new_root(element):
    new_root = etree.Element('xml')
    new_root.append(deepcopy(element))

    return etree.ElementTree(new_root)

def remove_unicode(text):
    return text.encode('ascii', 'ignore').decode('ascii').strip('\n')

def get_clean_tag_soup(query_result):
    if query_result is not None and len(query_result) > 0:
        return _get_clean_tag_soup(query_result[0])
    return BeautifulSoup("", 'html.parser')

def _get_clean_tag_soup(elem):
    soup = BeautifulSoup(etree.tostring(elem, method='xml'), 'html.parser').find(True)
    # clear tag
    del soup['xmlns:mml']
    del soup['xmlns:xlink']

    return soup

def get_clean_tag_string(query_result):
    return remove_unicode(str(get_clean_tag_soup(query_result)))

def _get_clean_tag_string(elem):
    return remove_unicode(str(_get_clean_tag_soup(elem)))

def extract_cells_from_table(html_string):
    soup = BeautifulSoup(html_string, 'html.parser')

    cells = []
    for row in soup.find_all('tr'):
        row_cells = [remove_unicode(cell.get_text(strip=True)) for cell in row.find_all(['th', 'td'])]
        cells.extend(row_cells)

    return cells

def extract_table(root, citations):
    tables = []

    tables_wrap = root.xpath("//table-wrap")
    for table_wrap in tables_wrap:
        table_wrap_id = table_wrap.get('id')
        # generate new root
        root_table = get_new_root(table_wrap)

        # xpath queries
        caption_query = root_table.xpath(f'//table-wrap[@id="{table_wrap_id}"]/caption')
        footer_query = root_table.xpath("//table-wrap-foot")
        thead_query = root_table.xpath(f"//table-wrap[@id='{table_wrap_id}']//table//thead")
        tbody_query = root_table.xpath(f"//table-wrap[@id='{table_wrap_id}']//table//tbody")

        # table body extraction
        table_body = get_clean_tag_string(thead_query) + get_clean_tag_string(tbody_query)
        table_cells = [{
            "content": cell,
            "cited_in": [
                _get_clean_tag_string(match)
                for match in root.xpath("//p[contains(string(.), $target_text)]", target_text=cell)
            ]
        } for cell in extract_cells_from_table(table_body) if cell != ""]

        tables.append({
            "table_id": table_wrap_id,
            "body": table_body,
            "cells": table_cells,
            "caption": extract_inner_content(caption_query),
            "caption_citations": find_citations(caption_query, citations),
            "foots": [_extract_inner_content(footer) for footer in footer_query],
            "paragraphs": extract_cited_paragraphs(root, 'table', table_wrap_id, citations)
        })

    return tables

def extract_figure(root, pmcid, citations):
    figures = []

    figures_wrap = root.xpath("//fig")
    for figure_wrap in figures_wrap:
        figure_wrap_id = figure_wrap.get('id')
        root_figure = get_new_root(figure_wrap)

        caption_query = root_figure.xpath('//caption')
        src_query = root_figure.xpath("//fig/*[local-name()='graphic']/@*[local-name()='href']")
        if src_query is not None and len(src_query) > 0:
            source_value = f'https://www.ncbi.nlm.nih.gov/pmc/articles/{pmcid}/bin/{src_query[0]}.jpg'
        else:
            source_value = ""

        figures.append({
            "fig_id": figure_wrap_id,
            "src": source_value,
            "caption": extract_inner_content(caption_query),
            "caption_citations": find_citations(caption_query, citations),
            "paragraphs": extract_cited_paragraphs(root, 'fig', figure_wrap_id, citations)
        })

    return figures

def extract_keywords(elements):
    if elements:
        kwd_elements = elements[0].xpath('.//kwd')
        return [kwd.text for kwd in kwd_elements if kwd.text is not None]

    return []


def extract_inner_text(elements):
    return remove_unicode(get_clean_tag_soup(elements).get_text())

def extract_inner_content(elements):
    return _extract_inner_content(elements[0]) if elements is not None and len(elements) > 0 else ""

def _extract_inner_content(elem):
    soup = _get_clean_tag_soup(elem)
    if len(soup.contents) == 0:
        return ""

    inner_content = soup.parent
    soup.unwrap()

    return remove_unicode(str(inner_content))

def find_citations(paragraph, citations):
    if paragraph is None or (isinstance(paragraph, list) and not paragraph):
        return []

    if isinstance(paragraph, list):
        paragraph = paragraph[0]

    citations_text = {}

    query = get_new_root(paragraph).xpath("//xref[@ref-type='bibr']")
    for result in query:
        citation_id = result.get('rid')
        if citation_id in citations:
            citations_text[citation_id] = citations[citation_id]

    return list(citations_text.values())

def extract_cited_paragraphs(root, ref_type, elem_id, citations):
    caption_citation = []

    query = root.xpath(f"//p[xref[@ref-type='{ref_type}' and @rid='{elem_id}']]")
    for paragraph in query:
        caption_citation.append({
            "text": remove_unicode(_get_clean_tag_string(paragraph)),
            "cited_in": find_citations(paragraph, citations)
        })

    return caption_citation

def extract_citations(root):
    citations = {}

    query = root.xpath("//ref-list/ref")
    for result in query:
        rid = result.get('id')
        citations[rid] = _get_clean_tag_string(result)

    return citations

def extract_data(path):
    root = get_root(path)
    # extract all citations from the document
    citations = extract_citations(root)

    pmcid = extract_inner_text(root.xpath("//article-id[@pub-id-type='pmc']"))
    extracted_data = {
        "pmcid": pmcid,
        "content": {
            "title": extract_inner_text(root.xpath("//title-group/article-title")),
            "abstract": extract_inner_content(root.xpath("//abstract")),
            "keywords": extract_keywords(root.xpath("//kwd-group")),
            "tables": extract_table(root, citations),
            "figures": extract_figure(root, pmcid, citations)
        }
    }

    return extracted_data
