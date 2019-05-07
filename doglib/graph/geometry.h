#pragma once
namespace doglib {
namespace graph {

struct Point {
    int row;
    int col;
    Point(int row, int col) : row(row), col(col) {}
    bool check_range(int R, int C) {
        return 0 <= row && row < R && 0 <= col && col < C;
    }
};

Point operator+(Point a, Point b) {
    return Point(a.row + b.row, a.col + b.col);
}

Point operator-(Point a, Point b) {
    return Point(a.row - b.row, a.col - b.col);
}

Point rotate_90_clockwise(Point target, Point root = Point(0, 0)) {
    Point diff = target - root;
    Point new_diff(diff.col, -diff.row);
    return root + new_diff;
}

Point rotate_90_anticlockwise(Point target, Point root = Point(0, 0)) {
    Point diff = target - root;
    Point new_diff(-diff.col, diff.row);
    return root + new_diff;
}

Point rotate_180(Point target, Point root = Point(0, 0)) {
    Point diff = target - root;
    Point new_diff(-diff.col, -diff.row);
    return root + new_diff;
}

bool operator==(Point a, Point b) {
    return a.row == b.row && a.col == b.col;
}

bool operator!=(Point a, Point b) {
    return !(a != b);
}

Point uf_grid_block(int row, int col) {
    return Point(row * 2 + 1, col * 2 + 1);
}

Point uf_grid_edge(int row, int col, int diff_r, int diff_c) {
    return uf_grid_block(row, col) + Point(diff_r, diff_c);
}

}    // namespace graph
}    // namespace doglib
