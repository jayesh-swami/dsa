import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class TimeBasedKeyValueStore {

    final Map<String, List<TimestampValue>> timestampValues;

    public TimeBasedKeyValueStore() {
        this.timestampValues = new HashMap<>();
    }

    public void set(String key, String value, int timestamp) {
        if(!timestampValues.containsKey(key)) {
            timestampValues.put(key, new ArrayList<>());
        }
        timestampValues.get(key).add(new TimestampValue(timestamp, value));
    }

    public String get(String key, int timestamp) {
        if(!timestampValues.containsKey(key)) return "";

        return searchValueForTimestamp(key, timestamp);
    }

    private String searchValueForTimestamp(String key, int timestamp) {
        List<TimestampValue> timestamps = this.timestampValues.get(key);

        int low = 0, high = timestamps.size() - 1;

        String result = "";

        while(low <= high) {
            int mid = (low + high) / 2;

            if(timestamps.get(mid).timestamp <= timestamp) {
                result = timestamps.get(mid).value;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return result;
    }

    record TimestampValue(int timestamp, String value) {
    }
}
