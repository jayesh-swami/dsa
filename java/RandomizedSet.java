import java.util.*;

public class RandomizedSet {

    List<Integer> setList = new ArrayList<>();
    Map<Integer, Integer> map = new HashMap<>();

    public RandomizedSet() {

    }

    public boolean insert(int val) {
        if (map.containsKey(val)) return false;

        setList.add(val);
        map.put(val, setList.size() - 1);

        return true;
    }

    public boolean remove(int val) {
        if (!map.containsKey(val)) return false;

        int index = map.get(val);

        setList.set(index, setList.get(setList.size() - 1));
        map.put(setList.get(index), index);

        setList.remove(setList.size() - 1);
        map.remove(val);

        return true;
    }

    public int getRandom() {
        Random rand = new Random();
        return setList.get(rand.nextInt(setList.size()));
    }
}
