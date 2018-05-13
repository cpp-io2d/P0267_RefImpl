#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <io2d.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental;
using namespace std::experimental::io2d;

class GameOfLife
{
public:
    GameOfLife(int board_width, int board_height);
    
    void Seed(int amount);
    void Tick();
    void Display(output_surface &surface);
    
private:
    enum class CellState : uint8_t {
        Off,
        Emerging,
        On,
        Fading
    };
    
    CellState At(int x, int y) const { return m_Cells.at(y*m_BoardWidth + x); }
    void CountNeighbours();
    void SweepIntermediates();
    void DrawGrid(output_surface &surface);
    void DrawCells(output_surface &surface);

    const float m_CellPxSize = 10.f;
    const nanoseconds m_CycleDuration = 300ms;
    const int m_BoardWidth;
    const int m_BoardHeight;
    time_point<high_resolution_clock> m_LastGenTime;
    float m_TransitionPoint = 0.f;
    vector<CellState> m_Cells;
    vector<uint8_t> m_Counts;
};

GameOfLife::GameOfLife(int board_width, int board_height):
    m_BoardWidth(board_width),
    m_BoardHeight(board_height)
{
    assert( board_width > 0 && board_height > 0 );
    m_Cells.resize(board_width * board_height, CellState::Off);
    m_Counts.resize(board_width * board_height);
}

void GameOfLife::Seed(int amount)
{
    auto random_engine = default_random_engine{random_device{}()};
    auto distribution = uniform_int_distribution<int>(0, m_BoardWidth * m_BoardHeight - 1);
    while( amount --> 0 )
        m_Cells[distribution(random_engine)] = CellState::On;
    m_LastGenTime = high_resolution_clock::now();
    m_TransitionPoint = 0.f;
}

void GameOfLife::CountNeighbours()
{
    auto wrap_x = [&](int x) { return (x + m_BoardWidth)  % m_BoardWidth;  };
    auto wrap_y = [&](int y) { return (y + m_BoardHeight) % m_BoardHeight; };
    auto at = [&](int x, int y) { return At(wrap_x(x), wrap_y(y)) == CellState::On; };
    pair<int, int> dirs[] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1} };
    for( auto y = 0; y < m_BoardHeight; ++y )
        for( auto x = 0; x < m_BoardWidth; ++x )
            m_Counts[y*m_BoardWidth + x] = accumulate(begin(dirs), end(dirs), 0, [&](auto a, auto b){
                return at(x + b.first, y + b.second) ? a + 1 : a;
            });
}

void GameOfLife::SweepIntermediates()
{
    auto f = [](CellState cs) -> CellState {
        if( cs == CellState::On || cs == CellState::Off ) return cs;
        if( cs == CellState::Emerging ) return CellState::On;
        return CellState::Off;
    };
    transform(begin(m_Cells), end(m_Cells), begin(m_Cells), f);
}

void GameOfLife::Tick()
{
    const auto now = high_resolution_clock::now();
    const auto delta = now - m_LastGenTime;
    if( delta < m_CycleDuration ) {
        m_TransitionPoint = float(delta.count()) / float(m_CycleDuration.count());
    }
    else {
        auto rules = [](CellState cs, int around) {
            return cs == CellState::On ?
                ( around == 2 || around == 3 ? CellState::On : CellState::Fading ) :
                ( around == 3 ? CellState::Emerging : CellState::Off );
        };
        SweepIntermediates();
        CountNeighbours();
        transform(begin(m_Cells), end(m_Cells), begin(m_Counts), begin(m_Cells), rules);
        m_LastGenTime = now;
        m_TransitionPoint = 0.f;
    }
}

void GameOfLife::Display(output_surface &surface)
{
    DrawGrid(surface);
    DrawCells(surface);
}

void GameOfLife::DrawCells(output_surface &surface)
{
    const auto on_brush = brush{rgba_color::black};
    const auto fading_brush = brush{rgba_color{0.f, 0.f, 0.f, 1.f - m_TransitionPoint}};
    const auto emerging_brush = brush{rgba_color{0.f, 0.f, 0.f, m_TransitionPoint}};
    
    const auto cell_size = m_CellPxSize - 1.f;
    for( auto y = 0; y < m_BoardHeight; ++y )
        for( auto x = 0; x < m_BoardWidth; ++x ) {
            auto state = At(x, y);
            if( state == CellState::On ) {
                auto bb = bounding_box{m_CellPxSize * x + 1, m_CellPxSize * y + 1, cell_size, cell_size};
                surface.paint(on_brush, nullopt, nullopt, clip_props{bb});
            }
            if( state == CellState::Fading ) {
                auto sz = cell_size  * (1.f - m_TransitionPoint);
                auto d = (cell_size - sz) / 2;
                auto bb = bounding_box{m_CellPxSize * x + 1 + d, m_CellPxSize * y + 1 + d, sz, sz};
                surface.paint(fading_brush, nullopt, nullopt, clip_props{bb});
            }
            if( state == CellState::Emerging ) {
                auto sz = cell_size * m_TransitionPoint;
                auto d = (cell_size - sz) / 2;
                auto bb = bounding_box{m_CellPxSize * x + 1 + d, m_CellPxSize * y + 1 + d, sz, sz};
                surface.paint(emerging_brush, nullopt, nullopt, clip_props{bb});
            }
        }
}

void GameOfLife::DrawGrid(output_surface &surface)
{
    surface.paint(brush{rgba_color::light_gray});
    
    auto b = brush{rgba_color::gray};
    auto sp = stroke_props{1., line_cap::none};
    auto dp = dashes{ 1.f, {1.f, 1.f} };
    for( auto i = 0; i < m_BoardWidth; ++i ) {
        auto pb = path_builder{};
        pb.new_figure({i*m_CellPxSize + 0.5f, 0.f});
        pb.rel_line({0.f, m_BoardHeight * m_CellPxSize});
        surface.stroke(b, pb, nullopt, sp, dp);
    }
    for( auto i = 0; i < m_BoardHeight; ++i ) {
        auto pb = path_builder{};
        pb.new_figure({0.f, i*m_CellPxSize + 0.5f});
        pb.rel_line({m_BoardWidth*m_CellPxSize, 0.f});
        surface.stroke(b, pb, nullopt, sp, dp);
    }
}

int main(int argc, char **argv)
{
    auto game = unique_ptr<GameOfLife>();    
    auto display = output_surface{500, 500, format::argb32, scaling::none, refresh_style::fixed, 30.f};    
    display.size_change_callback([&](output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](auto& surface) {
        if( !game ) {
            auto board_width = display.dimensions().x()/10;
            auto board_height = display.dimensions().y()/10;
            game = make_unique<GameOfLife>(board_width, board_height);    
            game->Seed((board_width * board_height) / 8);            
        }
        game->Tick();
        game->Display(surface);
    });
    display.begin_show();
}
