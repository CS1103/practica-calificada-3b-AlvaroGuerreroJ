#ifndef __BOARD_HPP_
#define __BOARD_HPP_

#include <functional>
#include <optional>
#include <ostream>
#include <set>
#include <vector>

class Board
{
private:
    /**
     * Each rectangle keeps memory of its size and initial position.
     */
    struct Rectangle
    {
public:
        size_t pos_x;
        size_t pos_y;
        size_t rows;
        size_t cols;

public:
        Rectangle(size_t pos_x, size_t pos_y, size_t rows, size_t cols);

        bool operator<(Rectangle const& other) const;
    };

private:
    size_t m_rows;
    size_t m_cols;

    // We keep a list of all the rectangles.
    std::set<Rectangle> m_rectangles;
    //  We need to keep information about which greater cell occupies each square
    // to facilitate checking if the new rectangle would fit within the existing
    // one.
    // XXX: How could I indent this line?
    std::vector<std::vector<
                    std::optional<std::reference_wrapper<Rectangle const>>
    >> m_board;

public:
    Board(size_t rows, size_t cols);

    bool insert(Rectangle&& rec);

    std::set<Rectangle> const& get_rectangles() const;
};

#endif // __BOARD_HPP_
