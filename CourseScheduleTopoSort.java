import java.util.*;

public class CourseScheduleTopoSort {

    Set<Integer> visited = new HashSet<>();
    Set<Integer> visiting = new HashSet<>();
    Map<Integer, List<Integer>> courseDep = new HashMap<>();
    Queue<Integer> orderOfCourses = new LinkedList<>();

    public int[] findOrder(int numCourses, int[][] prerequisites) {

        for (int i = 0; i < numCourses; i++) {
            courseDep.put(i, new ArrayList<>());
        }

        for (int i = 0; i < prerequisites.length; i++) {
            int course = prerequisites[i][0];
            int dep = prerequisites[i][1];

            courseDep.get(course).add(dep);
        }

        for (int i = 0; i < numCourses; i++) {
            if (!visited.contains(i)) {
                if (isCyclic(i)) return new int[]{};
            }
        }

        int[] res = new int[orderOfCourses.size()];

        for (int i = 0; i < res.length; i++) {
            res[i] = orderOfCourses.poll();
        }

        return res;
    }

    private boolean isCyclic(int course) {

        if (visiting.contains(course)) return true;

        visiting.add(course);

        for (Integer depCourse : courseDep.get(course)) {
            if (isCyclic(depCourse)) return true;
        }

        visiting.remove(course);
        if (!visited.contains(course)) orderOfCourses.add(course);

        visited.add(course);
        return false;
    }

}
