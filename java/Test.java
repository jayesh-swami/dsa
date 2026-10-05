import java.util.ArrayList;
import java.util.List;

class Test {

    public static void main(String[] args) {
        IntervalSplitAndLabel intervalSplitAndLabel = new IntervalSplitAndLabel();

        List<List<String>> in = new ArrayList<>();
        in.add(new ArrayList<>());

        in.get(0).add("10");
        in.get(0).add("110");
        in.get(0).add("David");

        in.add(new ArrayList<>());

        in.get(1).add("50");
        in.get(1).add("100");
        in.get(1).add("Ravid");

        in.add(new ArrayList<>());

        in.get(2).add("70");
        in.get(2).add("80");
        in.get(2).add("BEAM");

        in.add(new ArrayList<>());

        in.get(3).add("0");
        in.get(3).add("10");
        in.get(3).add("J");

        System.out.println(intervalSplitAndLabel.splitAndLabel(in));
    }

}