import java.util.ArrayList;
import java.util.List;

public class EncodeDecodeString {

    public String encode(List<String> strs) {
        StringBuilder result = new StringBuilder();

        for(String s: strs) {
            result.append(s.length()).append("#").append(s);
        }

        return result.toString();
    }

    public List<String> decode(String str) {
        List<String> result = new ArrayList<>();

        for(int i = 0 ; i < str.length() ;) {
            int j = i+1;
            while(str.charAt(j) != '#') j++;

            int len = Integer.parseInt(str.substring(i, j));

            result.add(str.substring(j+1, j + len + 1));
            i = j + len + 1;
        }

        return result;
    }

}
