/**
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/
package iotdb.interop;
import org.apache.iotdb.tsfile.file.header.PageHeader;
import org.apache.iotdb.tsfile.file.metadata.statistics.Statistics;
import org.apache.iotdb.tsfile.file.metadata.enums.TSDataType;
import java.io.FileOutputStream;
import java.nio.file.Paths;
import java.io.File;
/**
 * I will refactor this. WIP
 *  I think that is needed a directory data were we write serialized data
 */
public class App {
    public static final int UNCOMPRESSED_SIZE = 123456;
    public static final int COMPRESSED_SIZE = 100000;
    public static final int NUM_OF_VALUES = 10000;
    public static final long MAX_TIMESTAMO = 523372036854775806L;
    public static final long MIN_TIMESTAMO = 423372036854775806L;
    public static final TSDataType DATA_TYPE = TSDataType.INT64;
    public static void main(String[] args) {
        var path = args[0];
        var file = new File(path);
        if (file.isDirectory()) {
            testPageHeaderWrite(path);
        }
    }
    public static void testPageHeaderWrite(String path) {
        Statistics<?> statistics = Statistics.getStatsByType(App.DATA_TYPE);
        statistics.setEmpty(false);
        PageHeader pageHeader = new PageHeader(App.UNCOMPRESSED_SIZE, App.COMPRESSED_SIZE, NUM_OF_VALUES, statistics,MAX_TIMESTAMO,MIN_TIMESTAMO);
        serializePageHeader(path,pageHeader);
    }
    private static void serializePageHeader(String directory, PageHeader header) {
        String fileName = "pageHeader.dat";
        var filePath = Paths.get(directory, fileName);
        try {
            var fos = new FileOutputStream(filePath.toString());
            header.serializeTo(fos);
        } catch (Exception ex) {
            System.out.println("Exception writing serialized data"  + ex.getMessage());
        }
     }
}
