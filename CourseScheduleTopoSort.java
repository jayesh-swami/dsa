import java.util.*;

public class CourseScheduleTopoSort {

    private final Map<Integer, List<Integer>> dep = new HashMap<>();
    private final Set<Integer> visited = new HashSet<>();
    private Queue<Integer> topoSortRes = new LinkedList<>();

    public int[] findOrder(int numCourses, int[][] prerequisites) {
        Set<Integer> setOfNonDependentNodes = new HashSet<>();

        for (int i = 0; i < numCourses; i++) {
            dep.put(i, new ArrayList<>());
            setOfNonDependentNodes.add(i);
        }

        for (int[] prereq : prerequisites) {
            dep.get(prereq[0]).add(prereq[1]);
            if(setOfNonDependentNodes.contains(prereq[0]))
                setOfNonDependentNodes.remove(prereq[1]);
        }

        for (int i = 0; i < numCourses; i++) {
            Set<Integer> visitedCourses = new HashSet<>();
            if (cycleExists(i, visitedCourses)) return new int[]{};
        }

        for(Integer node: setOfNonDependentNodes){
            topoSort(node);
        }

        int[] result = new int[numCourses];

        for(int i = 0 ; i < numCourses ; i++) {
            result[i] = topoSortRes.poll();
        }

        return result;
    }

    private boolean cycleExists(
            int courseNum,
            Set<Integer> visitedCourses) {

        if (visitedCourses.contains(courseNum)) return true;

        visitedCourses.add(courseNum);

        boolean result = false;

        if (!dep.containsKey(courseNum)) return false;

        for (int i = 0; i < dep.get(courseNum).size(); i++) {
            result = result || cycleExists(dep.get(courseNum).get(i), visitedCourses);
        }

        // Very important to remove
        visitedCourses.remove(courseNum);

        return result;
    }

    private void topoSort(int courseNum) {
        if(visited.contains(courseNum)) return;

        for(Integer adjacentNode: dep.get(courseNum)) {
            topoSort(adjacentNode);
        }

        visited.add(courseNum);
        topoSortRes.add(courseNum);
    }

}
