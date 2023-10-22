package lucene;

import org.apache.lucene.analysis.en.EnglishAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static utils.Constants.*;

public class QueryRunner {

    private IndexSearcher searcher;

    private QueryParser titleParser;
    private QueryParser contentParser;

    public QueryRunner(IndexSearcher searcher) {
        this.searcher = searcher;

        this.titleParser = new QueryParser(TITLE, new EnglishAnalyzer());
        this.contentParser = new QueryParser(CONTENT, new EnglishAnalyzer());
    }

    public List<Document> execute(String userInput) throws IOException {
        Query query = this.makeQuery(userInput);
        TopDocs hit = searcher.search(query, NUMBER_TOP_DOCS);

        return this.getDocumentsFound(hit);
    }

    private Query makeQuery(String userInput) {
        try {
            return new BooleanQuery.Builder()
                    .add(new BooleanClause(titleParser.parse(userInput), BooleanClause.Occur.SHOULD))
                    .add(new BooleanClause(contentParser.parse(userInput), BooleanClause.Occur.SHOULD))
                    .build();
        } catch (ParseException e) {
            return new MatchAllDocsQuery();
        }
    }

    private List<Document> getDocumentsFound(TopDocs hits) throws IOException {
        List<Document> docsFound = new ArrayList<>();
        for (int i = 0; i < hits.scoreDocs.length; i++) {
            docsFound.add(this.searcher.doc(hits.scoreDocs[i].doc));
        }

        return docsFound;
    }

}
