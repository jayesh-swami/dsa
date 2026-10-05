import java.util.*;

public class CourseScheduleCycleDetection {
    private final Map<Integer, List<Integer>> dep = new HashMap<>();

    public boolean canFinish(int numCourses, int[][] prerequisites) {

        for (int i = 0; i < numCourses; i++) {
            dep.put(i, new ArrayList<>());
        }

        for (int[] prereq : prerequisites) {
            dep.get(prereq[0]).add(prereq[1]);
        }


        for (int i = 0; i < numCourses; i++) {
            Set<Integer> visitedCourses = new HashSet<>();
            if (cycleExists(i, visitedCourses)) return false;
        }

        return true;
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
}
