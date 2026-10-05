import java.util.*;

public class LoggerRateLimiter {
    private final Map<String, Integer> lastPrintedMessage = new HashMap<>();

    public boolean couldPrintMessage(int timestamp, String message) {

        if(!lastPrintedMessage.containsKey(message) ||
                timestamp - lastPrintedMessage.get(message)  >= 10) {

            lastPrintedMessage.put(message, timestamp);
            return true;
        }

        return false;
    }
}
