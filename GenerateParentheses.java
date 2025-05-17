import java.util.ArrayList;
import java.util.List;

public class GenerateParentheses {

    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();

        addString(n, "", 0, 0, result);
        return result;
    }

    private void addString(
            int n,
            String untilNow,
            int open,
            int close,
            List<String> res) {
        if(close > open) return;
        if(untilNow.length() > 2 * n) return;

        if(untilNow.length() == 2 * n && open == close) {
            res.add(untilNow);
            return;
        }

        addString(n, untilNow + "(", open + 1, close, res);
        addString(n, untilNow + ")", open, close + 1, res);
        return;
    }

}
