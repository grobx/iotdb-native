public class HeaderInterop {
    public static String testPageHeaderWrite() {
        PageHeader pageHeader =  new PageHeader(PageHeaderTest.UNCOMPRESSED_SIZE, PageHeaderTest.COMPRESSED_SIZE,
            new Statistics();
        return serializePageHeader(pageHeader)
    }
    public static String testPageHeaderWrite() {
            PageHeader pageHeader =  new PageHeader(PageHeaderTest.UNCOMPRESSED_SIZE, PageHeaderTest.COMPRESSED_SIZE,
                new Statistics();
            return serializePageHeader(pageHeader)
    }
    private static String serializePageHeader(PageHeader header) {
        ByteArrayOutputStream fos = new ByteArrayOutputStream();
        header.serializeTo(fos);
        fos.Close()
        return fos.toString();
     }
}