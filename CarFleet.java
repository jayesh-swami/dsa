import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Dont know why this was in stack but we can simply just check how many cars catch up to a specific car
 */

public class CarFleet {

    public int carFleet(int target, int[] position, int[] speed) {

        List<CarData> cars = new ArrayList<>();

        for(int i = 0; i < position.length ; i++) {
            cars.add(new CarData(position[i], speed[i]));
        }

        Collections.sort(cars);

        int fleets = 0;

        for(int i=cars.size() - 1 ; i >= 0 ; i--) {
            fleets++;
            int j = i;
            while(i > 0 && carCatches(cars.get(i-1), cars.get(j), target)) i--;
        }

        return fleets;
    }

    private static boolean carCatches(
            CarData a,
            CarData b,
            int target) {
        float timeForA = Float.intBitsToFloat(target - a.position) / Float.intBitsToFloat(a.speed);
        float timeForB = Float.intBitsToFloat(target - b.position) / Float.intBitsToFloat(b.speed);
        return timeForA <= timeForB;
        // Or a simplified condition without float -return (target - a.position)*b.speed <= (target - b.position)*a.speed;
    }

    static class CarData implements Comparable<CarData> {
        int position;
        int speed;

        CarData(int p, int s) {
            this.position = p;
            this.speed = s;
        }

        @Override
        public int compareTo(CarData o) {
            return this.position - o.position;
        }
    }
}
