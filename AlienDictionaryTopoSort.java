import java.util.*;

public class AlienDictionaryTopoSort {
    Map<Character, Set<Character>> depList;
    Queue<Character> characterOrder = new LinkedList<>();
    Set<Character> visited = new HashSet<>();
    Set<Character> visiting = new HashSet<>();

    public String foreignDictionary(String[] words) {
        depList = new HashMap<>();

        addToDepList(words[0]);

        for (int i = 1; i < words.length; i++) {
            String currentWord = words[i];
            String previousWord = words[i - 1];

            addToDepList(currentWord);
            addToDepList(previousWord);

            int minLength = Math.min(currentWord.length(), previousWord.length());

            for (int j = 0; j < minLength; j++) {
                if (currentWord.charAt(j) == previousWord.charAt(j)) {
                    if (j == minLength - 1 && currentWord.length() == minLength && previousWord.length() > currentWord.length())
                        return "";
                    continue;
                } else {
                    depList.get(currentWord.charAt(j)).add(previousWord.charAt(j));
                    break;
                }
            }
        }

        for (Character c : depList.keySet())
            if (!visited.contains(c)) if (topoSortWithCycleCheck(c)) return "";

        StringBuilder s = new StringBuilder();

        while (!characterOrder.isEmpty()) s.append(characterOrder.poll());

        return s.toString();
    }

    private boolean topoSortWithCycleCheck(Character c) {
        if (visiting.contains(c)) return true;

        visiting.add(c);

        for (Character nextChar : depList.get(c))
            if (topoSortWithCycleCheck(nextChar)) return true;

        if (!visited.contains(c)) characterOrder.add(c);

        visiting.remove(c);
        visited.add(c);

        return false;
    }

    private void addToDepList(String s) {
        for (int i = 0; i < s.length(); i++)
            depList.putIfAbsent(s.charAt(i), new HashSet<>());
    }
}
