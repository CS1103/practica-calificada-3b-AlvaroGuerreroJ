#include <functional>
#include <ostream>
#include <set>

#include "Board.hpp"

Board::Rectangle::Rectangle(size_t pos_x, size_t pos_y,
                            size_t rows, size_t cols)
    : pos_x(pos_x), pos_y(pos_y), rows(rows), cols(cols)
{
}

bool Board::Rectangle::operator<(Rectangle const& other) const
{
    if (this->pos_x != other.pos_x)
    {
        return this->pos_x < other.pos_x;
    }
    else if (this->pos_y != other.pos_y)
    {
        return this->pos_y < other.pos_y;
    }
    else if (this->rows != other.rows)
    {
        return this->rows < other.rows;
    }
    else
    {
        return this->cols < other.cols;
    }
}

Board::Board(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols), m_board(m_rows)
{
    for (auto& r : m_board)
    {
        r.resize(m_cols);
    }
}

bool Board::insert(Rectangle&& rec)
{
    // Check if the rectangle fit between the boundaries
    // Because the positions and the sizes are unsigned, we can check only for
    // pos_x + rows and pos_y + cols.
    if (rec.pos_x + rec.rows >= m_rows ||
        rec.pos_y + rec.cols >= m_cols)
    {
        return false;
    }

    // We are gonna keep a list of the positions already seen as to avoid
    // repeating checks for the same rectangle.
    std::set<Rectangle> already_seen;
    // Check if any of the positions inside the would-be rectangle are filled.
    for (size_t i = rec.pos_x; i < rec.pos_x + rec.rows; i++)
    {
        for (size_t j = rec.pos_y; j < rec.pos_y + rec.cols; j++)
        {
            // If a position is filled, we have to check if our new rectangle
            // could fill inside the one already there.
            if (m_board[i][j].has_value())
            {
                auto const& r = m_board[i][j].value().get();

                //  If it was already seen, then it was already deemed valid
                if (already_seen.count(r) != 0)
                {
                    continue;
                }

                if (r.pos_x > rec.pos_x ||
                    r.pos_x + r.rows < rec.pos_x + rec.rows ||
                    r.pos_y > rec.pos_y ||
                    r.pos_y + r.cols < rec.pos_y + rec.cols)
                {
                    return false;
                }

                already_seen.insert(r);
            }
        }
    }

    // If we got here we can proceed to add the new rectangle
    m_rectangles.insert(rec);
    for (size_t i = rec.pos_x; i < rec.pos_x + rec.rows; i++)
    {
        for (size_t j = rec.pos_y; j < rec.pos_y + rec.cols; j++)
        {
            m_board[i][j] = std::cref(*m_rectangles.find(rec));
        }
    }

    return true;
}

std::set<Board::Rectangle> const& Board::get_rectangles() const
{
    return m_rectangles;
}
