package lucene;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.core.WhitespaceAnalyzer;
import org.apache.lucene.analysis.en.EnglishAnalyzer;
import org.apache.lucene.analysis.miscellaneous.PerFieldAnalyzerWrapper;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import static utils.Constants.*;


public class IndexDocs {

    public IndexDocs() {}

    public void createIndex(Directory indexDirectory) throws IOException {
        Analyzer analyzer = this.getAnalyzer();
        IndexWriterConfig config = new IndexWriterConfig(analyzer);

        IndexWriter writer = new IndexWriter(indexDirectory, config);
        this.writeIndex(writer);
    }

    private void writeIndex(IndexWriter writer) throws IOException {
        writer.deleteAll();

        Arrays.stream(Objects.requireNonNull(new File(STORAGE_DIRECTORY).listFiles()))
                .filter(File::isFile)
                .forEach(file -> {
                    try {
                        writer.addDocument(this.getDocument(file));
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                });

        writer.commit();
        writer.close();
    }

    private Document getDocument(File file) throws IOException {
        Document doc = new Document();
        doc.add(new TextField(TITLE, file.getName().replace(FILE_FORMAT, ""), Field.Store.YES));
        doc.add(new TextField(CONTENT, new String(Files.readAllBytes(file.toPath())), Field.Store.YES));

        return doc;
    }

    private Analyzer getAnalyzer() {
        Analyzer defaultAnalyzer = new StandardAnalyzer();

        Map<String, Analyzer> perFieldAnalyzers = new HashMap<>();
        perFieldAnalyzers.put(TITLE, new EnglishAnalyzer());
        perFieldAnalyzers.put(CONTENT, new EnglishAnalyzer());

        return  new PerFieldAnalyzerWrapper(defaultAnalyzer, perFieldAnalyzers);
    }
}

