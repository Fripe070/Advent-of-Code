package day1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

public class Day1 {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length != 1) {
            System.err.println("Must provide an input file path");
            System.exit(1);
        }
        var inFile = new FileReader(args[0]);
        var offsets = getOffsets(inFile);
        part1(offsets);
        part2(offsets);
    }

    public static void part1(ArrayList<Integer> offsets) {
        int zeroCounter = 0;
        int dial = 50;
        for (Integer offset : offsets) {
            if (offset == 0) continue;
            dial += offset;
            while (dial < 0) dial += 100;
            while (dial >= 100) dial -= 100;
            if (dial == 0) zeroCounter++;
        }
        System.out.println("Part1: Number of zeros: " + zeroCounter);
    }

    public static void part2(ArrayList<Integer> offsets) {
        int zeroCounter = 0;
        int dial = 50;
        for (Integer offset : offsets) {
            if (offset == 0) continue;
            int offsetSign = offset < 0 ? -1 : 1;
            for (int i = 0; i < Math.abs(offset); i++) {
                dial += offsetSign;
                if (dial < 0) dial += 100;
                if (dial >= 100) dial -= 100;
                if (dial == 0) zeroCounter++;
            }
        }
        System.out.println("Part1: Number of zeros: " + zeroCounter);
    }

    private static ArrayList<Integer> getOffsets(FileReader infile) {
        var scanner = new Scanner(infile);
        var offsets = new ArrayList<Integer>();
        while (scanner.hasNextLine()) {
            var line = scanner.nextLine();
            if (line.isEmpty()) continue;
            boolean leftTurning = line.startsWith("L");
            if (!leftTurning && !line.startsWith("R"))
                throw new RuntimeException("Line is neither a left or right turn.");
            int steps = Integer.parseInt(line.substring(1));
            int offset = steps * (leftTurning ? -1 : 1);
            offsets.add(offset);
        }
        return offsets;
    }
}
