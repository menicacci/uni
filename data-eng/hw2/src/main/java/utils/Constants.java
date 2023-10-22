package utils;

public class Constants {

    private Constants() {}

    public static final String CONTENT = "Content";
    public static final String TITLE = "Title";

    public static final String CONTENT_SEPARATOR = "&";
    public static final String FILE_FORMAT = ".txt";
    public static final String DATA_FILENAME = "documents_data.txt";
    public static final String STORAGE_DIRECTORY = "documents";
    public static final String INDEX_DIRECTORY = "target/idx";

    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_CYAN = "\u001B[36m";
    private static final String ANSI_RESET_COLOR = "\u001B[0m";

    public static final String FAILED_GENERATION_MESSAGE = "Failed to generate the documents";
    public static final String INITIAL_MESSAGE =
            ANSI_GREEN +
            "This is a simple search demo using Apache Lucene.\n" +
            "The articles are AI generated and related to football.\n" +
            "Press ENTER to exit.\n" +
                    ANSI_RESET_COLOR;
    public static final String TYPE_MESSAGE = "\nType a search:\t";
    public static final String ENDING_MESSAGE = "Program stopped.\n";
    public static final String NO_FOUND_MESSAGE = "\nNothing has been found\n";
    public static final String FOUND_MESSAGE = "\nSearch results:";
    public static final String DOC_FOUND_TITLE_MESSAGE = ANSI_CYAN + TITLE + ": " + ANSI_RESET_COLOR;
    public static final String DOC_FOUND_CONTENT_MESSAGE = ANSI_CYAN + CONTENT + ": " + ANSI_RESET_COLOR;

    public static final Integer NUMBER_TOP_DOCS = 3;

}
