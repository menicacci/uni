package lucene;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import static utils.Constants.*;

public class DocsGeneration {

    public static void initiate() {
        new DocsGeneration();
    }

    private List<String> titleList;
    private List<String> contentList;

    public DocsGeneration() {
        this.generateDocuments();
    }

    public void generateDocuments() {
        try {
            this.readData();

            File directory = new File(STORAGE_DIRECTORY);
            if (!directory.exists()) {
                directory.mkdir();
            }
            this.writeDocuments();
        } catch (IOException e) {
            System.out.println(FAILED_GENERATION_MESSAGE);
        }
    }

    private void readData() throws IOException {
        this.titleList = new ArrayList<>();
        this.contentList = new ArrayList<>();

        BufferedReader br = new BufferedReader(new FileReader(DATA_FILENAME));
        String line;
        while ((line = br.readLine()) != null) {
            String[] article = line.split(CONTENT_SEPARATOR);
            if (article.length == 2) {
                titleList.add(article[0]);
                contentList.add(article[1]);
            }
        }
    }

    private void writeDocuments() throws IOException {
        for (int i = 0; i < this.titleList.size(); i++) {
            String filePath = STORAGE_DIRECTORY + File.separator + this.titleList.get(i) + FILE_FORMAT;

            FileWriter writer = new FileWriter(filePath);
            writer.write(this.contentList.get(i));
        }
    }

}

