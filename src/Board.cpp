#include <functional>
#include <set>

#include "Board.hpp"

Board::Rectangle::Rectangle(size_t pos_x, size_t pos_y,
                            size_t rows, size_t cols)
    : m_pos_x(pos_x), m_pos_y(pos_y), m_rows(rows), m_cols(cols)
{
}

bool Board::Rectangle::operator<(Rectangle const& other) const
{
    if (this->m_pos_x != other.m_pos_x)
    {
        return this->m_pos_x < other.m_pos_x;
    }
    else if (this->m_pos_y != other.m_pos_y)
    {
        return this->m_pos_y < other.m_pos_y;
    }
    else if (this->m_rows != other.m_rows)
    {
        return this->m_rows < other.m_rows;
    }
    else
    {
        return this->m_cols < other.m_cols;
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
    if (rec.m_pos_x + rec.m_rows >= m_rows ||
        rec.m_pos_y + rec.m_cols >= m_cols)
    {
        return false;
    }

    // We are gonna keep a list of the positions already seen as to avoid
    // repeating checks for the same rectangle.
    std::set<std::reference_wrapper<Rectangle const>> already_seen;
    // Check if any of the positions inside the would-be rectangle are filled.
    for (size_t i = rec.m_pos_x; i < rec.m_pos_x + rec.m_rows; i++)
    {
        for (size_t j = rec.m_pos_y; j < rec.m_pos_y + rec.m_cols; j++)
        {
            // If a position is filled, we have to check if our new rectangle
            // could fill inside the one already there.
            if (m_board[i][j].has_value())
            {
                auto r_wrap = m_board[i][j].value();

                //  If it was already seen, then it was already deemed valid
                if (already_seen.count(r_wrap) != 0)
                {
                    continue;
                }

                auto const& r = r_wrap.get();

                if (r.m_pos_x > rec.m_pos_x || r.m_pos_y > rec.)

                already_seen.insert(r_wrap);
            }
        }
    }

    // If we got here we can proceed to add the new rectangle
}
