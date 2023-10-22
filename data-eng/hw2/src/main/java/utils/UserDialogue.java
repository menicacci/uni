package utils;

import lucene.IndexDocs;
import lucene.QueryRunner;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Scanner;

import static utils.Constants.*;

public class UserDialogue {

    private QueryRunner queryRunner;

    public static void initiate() throws IOException {
        new UserDialogue();
    }

    public UserDialogue() throws IOException {
        Path path = Paths.get(INDEX_DIRECTORY);
        try (Directory directory = FSDirectory.open(path)) {
            new IndexDocs().createIndex(directory);

            try (IndexReader reader = DirectoryReader.open(directory)) {
                IndexSearcher searcher = new IndexSearcher(reader);
                this.queryRunner = new QueryRunner(searcher);

                this.start();
            } finally {
                directory.close();
            }
        }
    }

    private void start() throws IOException {
        System.out.print(INITIAL_MESSAGE);
        System.out.println(TYPE_MESSAGE);

        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String userInput = scanner.nextLine();
            if (userInput.isEmpty()) {
                break;
            }
            else {
                this.showResults(userInput);
            }

            System.out.println(TYPE_MESSAGE);
        }
        System.out.println(ENDING_MESSAGE);
        scanner.close();
    }

    private void showResults(String userInput) throws IOException {
        List<Document> searchResult = queryRunner.execute(userInput);

        if (!searchResult.isEmpty()) {
            System.out.println(FOUND_MESSAGE);
            searchResult.forEach(result -> this.showDocument(result));
        }
        else {
            System.out.println(NO_FOUND_MESSAGE);
        }
    }

    private void showDocument(Document result) {
        System.out.println(DOC_FOUND_TITLE_MESSAGE + result.getValues(TITLE)[0]);
        System.out.println(DOC_FOUND_CONTENT_MESSAGE + result.getValues(CONTENT)[0]);
        System.out.println();
    }

}
