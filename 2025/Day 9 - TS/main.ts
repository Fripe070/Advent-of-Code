import { dir } from "node:console";
import { readFileSync, unwatchFile } from "node:fs";
import { join } from "node:path";

const filePath = process.argv[2];
if (!filePath) {
  console.error(
    "Please provide the input file path as a command line argument."
  );
  process.exit(1);
}
const input = readFileSync(join(import.meta.dirname, filePath), "utf-8").trim();

interface Point {
  x: number;
  y: number;
}
type Line = [Point, Point];

const pts = (p: Point): string => `${p.x},${p.y}`;
const padd = (p: Point, delta: Point): Point => ({
  x: p.x + delta.x,
  y: p.y + delta.y,
});
const normalize = (v: number): number => (v === 0 ? 0 : v > 0 ? 1 : -1);
function getArea(tile1: Point, tile2: Point) {
  const dx = Math.abs(tile2.x - tile1.x) + 1;
  const dy = Math.abs(tile2.y - tile1.y) + 1;
  return dy * dx;
}

function* interpolate(p1: Point, p2: Point): Generator<Point> {
  const dx = normalize(p2.x - p1.x);
  const dy = normalize(p2.y - p1.y);
  if (dx !== 0 && dy !== 0) throw new Error("Line not horizontal or vertical");
  let current = { ...p1 };
  yield { ...current };
  while (current.x !== p2.x || current.y !== p2.y) {
    current = {
      x: current.x + dx,
      y: current.y + dy,
    };
    yield { ...current };
  }
}

let tiles: Point[] = input.split("\n").map((l) => {
  const [x, y] = l.split(",");
  return { x: parseInt(x), y: parseInt(y) };
});
const xValues: number[] = tiles.map((t) => t.x).sort((a, b) => a - b);
const yValues: number[] = tiles.map((t) => t.y).sort((a, b) => a - b);
const xMap = new Map<number, number>();
const yMap = new Map<number, number>();
for (const [index, x] of xValues.entries()) {
  xMap.set(x, index);
}
for (const [index, y] of yValues.entries()) {
  yMap.set(y, index);
}
const packedTiles = tiles.map((t) => ({
  x: xMap.get(t.x)!,
  y: yMap.get(t.y)!,
}));

const borderPoints: Set<string> = new Set();
for (let index = 0; index < tiles.length; index++) {
  const tile1 = tiles[index];
  const tile2 = tiles[(index + 1) % tiles.length];
  for (const p of interpolate(tile1, tile2)) {
    borderPoints.add(pts(p));
  }
}
const tileSet: Set<string> = new Set(tiles.map((t) => pts(t)));

// Part 1
{
  let currentMax = 0;
  const unchecked: Point[] = [...tiles];
  while (unchecked.length > 0) {
    const tile1 = unchecked.pop()!;
    unchecked.forEach((tile2) => {
      const area = getArea(tile1, tile2);
      currentMax = Math.max(currentMax, area);
    });
  }
  console.log("Part 1:", currentMax);
}

// Part 2
{
  const lines: Line[] = [];
  tiles.forEach((tile, index) => {
    const nextTile = tiles[(index + 1) % tiles.length];
    lines.push([tile, nextTile]);
  });

  const directions = ["north", "east", "south", "west"] as const;
  type Direction = (typeof directions)[number];
  interface DirectionVectors {
    forward: Point;
    left: Point;
    right: Point;
    backward: Point;
  }
  const getDir = (line: Line): Direction => {
    const [start, end] = line;
    if (start.x === end.x) {
      return start.y > end.y ? "north" : "south";
    } else {
      return start.x < end.x ? "east" : "west";
    }
  };
  const getVectors = (dir: Direction): DirectionVectors => {
    const up = { x: 0, y: -1 };
    const down = { x: 0, y: 1 };
    const left = { x: -1, y: 0 };
    const right = { x: 1, y: 0 };
    switch (dir) {
      case "north":
        return { forward: up, left: left, right: right, backward: down };
      case "south":
        return { forward: down, left: right, right: left, backward: up };
      case "west":
        return { forward: left, left: down, right: up, backward: right };
      case "east":
        return { forward: right, left: up, right: down, backward: left };
    }
  };

  const lineRectIntersect = (line: Line, rect: [Point, Point]): boolean => {
    const rectMin = {
      x: Math.min(rect[0].x, rect[1].x),
      y: Math.min(rect[0].y, rect[1].y),
    };
    const rectMax = {
      x: Math.max(rect[0].x, rect[1].x),
      y: Math.max(rect[0].y, rect[1].y),
    };
    const [p1, p2] = line;
    // Line is vertical
    if (p1.x === p2.x) {
      if (p1.x < rectMin.x || p1.x > rectMax.x) return false;
      if (Math.max(p1.y, p2.y) < rectMin.y || Math.min(p1.y, p2.y) > rectMax.y)
        return false;
      return true;
    }
    // Line is horizontal
    if (p1.y === p2.y) {
      if (p1.y < rectMin.y || p1.y > rectMax.y) return false;
      if (Math.max(p1.x, p2.x) < rectMin.x || Math.min(p1.x, p2.x) > rectMax.x)
        return false;
      return true;
    }
    throw new Error("Line is not axis-aligned");
  };

  const turns = lines.reduce((acc, line, index) => {
    const nextLine = lines[(index + 1) % lines.length];
    const dir1 = directions.indexOf(getDir(line));
    const dir2 = directions.indexOf(getDir(nextLine));
    return acc + normalize(dir2 - dir1);
  }, 0);
  const clockwise = turns > 0;

  const outsideLines: Line[] = [];
  for (const [index, line] of lines.entries()) {
    const [start, end] = line;
    const directions = getVectors(getDir(line));
    // prettier-ignore
    let offsetStart = padd(start, clockwise ? directions.left : directions.right);
    let offsetEnd = padd(end, clockwise ? directions.left : directions.right);

    if (borderPoints.has(pts(offsetStart)))
      offsetStart = padd(offsetStart, directions.forward);
    if (borderPoints.has(pts(offsetEnd)))
      offsetEnd = padd(offsetEnd, directions.backward);

    outsideLines.push([offsetStart, offsetEnd]);

    if (borderPoints.has(pts(offsetStart)))
      throw new Error("Cannot find outside offset for start point");
    if (borderPoints.has(pts(offsetEnd)))
      throw new Error("Cannot find outside offset for end point");
  }

  let currentMax = 0;
  let maxRect: [Point, Point] | null = null;
  const unchecked: Point[] = [...tiles.map((t) => ({ ...t }))];
  while (unchecked.length > 0) {
    const tile1 = unchecked.pop()!;
    unchecked.forEach((tile2) => {
      const area = getArea(tile1, tile2);
      // console.log("Testing", tile1, tile2, "area", area);
      if (area <= currentMax) return;
      let anyIntersect = false;
      for (const line of outsideLines) {
        if (lineRectIntersect(line, [tile1, tile2])) {
          anyIntersect = true;
          // console.log("fail between", tile1, tile2, "due to line", line);
          break;
        }
      }
      if (!anyIntersect) {
        currentMax = area;
        maxRect = [tile1, tile2];
      }
    });
  }
  console.log("Part 2:", currentMax);

  {
    let maxX = -Infinity;
    let maxY = -Infinity;
    let minX = Infinity;
    let minY = Infinity;
    for (const tile of tiles) {
      maxX = Math.max(maxX, tile.x);
      maxY = Math.max(maxY, tile.y);
      minX = Math.min(minX, tile.x);
      minY = Math.min(minY, tile.y);
    }
    if ((maxY - minY) * (maxX - minX) > 10_000) {
      console.log("Area too large, skipping debug output");
    } else {
      // Visualise the map
      for (let y = minY - 1; y <= maxY + 1; y++) {
        const row2: string[] = [];
        for (let x = minX - 1; x <= maxX + 1; x++) {
          // Check if inside of the max rect
          const rectMin = {
            x: maxRect ? Math.min(maxRect[0].x, maxRect[1].x) : Infinity,
            y: maxRect ? Math.min(maxRect[0].y, maxRect[1].y) : Infinity,
          };
          const rectMax = {
            x: maxRect ? Math.max(maxRect[0].x, maxRect[1].x) : -Infinity,
            y: maxRect ? Math.max(maxRect[0].y, maxRect[1].y) : -Infinity,
          };
          if (
            maxRect &&
            x >= rectMin.x &&
            x <= rectMax.x &&
            y >= rectMin.y &&
            y <= rectMax.y
          ) {
            row2.push("*");
            continue;
          }
          const point: Point = { x, y };
          let intersected = false;
          for (const line of outsideLines) {
            if (lineRectIntersect(line, [point, point])) {
              intersected = true;
              break;
            }
          }
          row2.push(
            intersected
              ? "X"
              : tileSet.has(pts(point))
              ? "@"
              : borderPoints.has(pts(point))
              ? "#"
              : "."
          );
        }
        console.log(row2.join(""));
      }
    }
  }
  console.log("Max Rect:", maxRect);
}
