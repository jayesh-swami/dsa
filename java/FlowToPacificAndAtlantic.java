import java.util.*;

public class FlowToPacificAndAtlantic {
    public List<List<Integer>> pacificAtlantic(int[][] heights) {

        boolean[][] canFlowToPacific = new boolean[heights.length][heights[0].length];
        boolean[][] canFlowToAtlantic = new boolean[heights.length][heights[0].length];

        for (int i = 0; i < heights.length; i++) {
            for (int j = 0; j < heights[i].length; j++) {
                canFlowToPacific[i][j] = false;
                canFlowToAtlantic[i][j] = false;
            }
        }

        for (int i = 0; i < heights.length; i++) {
            if (!canFlowToPacific[i][0]) {
                flowUp(heights, i, 0, canFlowToPacific, Integer.MIN_VALUE);
            }

            if (!canFlowToAtlantic[i][heights[0].length - 1]) {
                flowUp(heights, i, heights[0].length - 1, canFlowToAtlantic, Integer.MIN_VALUE);
            }
        }

        for (int i = 0; i < heights[0].length; i++) {
            if (!canFlowToPacific[0][i]) {
                flowUp(heights, 0, i, canFlowToPacific, Integer.MIN_VALUE);
            }

            if (!canFlowToAtlantic[heights.length - 1][i]) {
                flowUp(heights, heights.length - 1, i, canFlowToAtlantic, Integer.MIN_VALUE);
            }
        }

        List<List<Integer>> result = new ArrayList<>();

        for (int i = 0; i < heights.length; i++) {
            for (int j = 0; j < heights[i].length; j++) {
                if (canFlowToPacific[i][j] && canFlowToAtlantic[i][j]) {
                    result.add(new ArrayList<>(List.of(i, j)));
                }
            }
        }

        return result;
    }

    private void flowUp(int[][] heights, int i, int j, boolean[][] canFlow, int prevHeight) {
        if (i < 0 || j < 0 || i >= heights.length
                || j >= heights[i].length || heights[i][j] < prevHeight || canFlow[i][j]) return;

        if (heights[i][j] >= prevHeight) canFlow[i][j] = true;

        flowUp(heights, i + 1, j, canFlow, heights[i][j]);
        flowUp(heights, i - 1, j, canFlow, heights[i][j]);
        flowUp(heights, i, j + 1, canFlow, heights[i][j]);
        flowUp(heights, i, j - 1, canFlow, heights[i][j]);
    }
}
