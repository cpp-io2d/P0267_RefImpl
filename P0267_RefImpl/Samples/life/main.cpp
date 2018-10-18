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
    interpreted_path m_CellFigure;    
};

GameOfLife::GameOfLife(int board_width, int board_height):
    m_BoardWidth(board_width),
    m_BoardHeight(board_height)
{
    assert( board_width > 0 && board_height > 0 );
    m_Cells.resize(board_width * board_height, CellState::Off);
    m_Counts.resize(board_width * board_height);
    m_CellFigure = [&]{
        const auto cell_size = m_CellPxSize - 1.f;
        auto pb = path_builder{};
        pb.new_figure({1.f, 1.f});
        pb.rel_line({cell_size, 0.f});
        pb.rel_line({0.f, cell_size});
        pb.rel_line({-cell_size, 0.f});
        pb.rel_line({0.f, -cell_size});
        pb.close_figure();
        return interpreted_path{pb};        
    }();  
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
    auto beta = m_TransitionPoint;
    auto gamma = 1.f - m_TransitionPoint;    
    const auto on_brush = brush{rgba_color::black};
    const auto fading_brush = brush{rgba_color{0.5f*beta, 0.5f*beta, 0.5f*beta}};
    const auto emerging_brush = brush{rgba_color{0.5f*gamma, 0.5f*gamma, 0.5f*gamma}};
    const auto cell_size = m_CellPxSize - 1.f;
	const auto min_scale = 0.01f;
        
    for( auto y = 0; y < m_BoardHeight; ++y )
        for( auto x = 0; x < m_BoardWidth; ++x ) {
            auto state = At(x, y);
            auto rp = render_props{};
            rp.compositing(compositing_op::source);
            if( state == CellState::On ) {
                rp.surface_matrix(matrix_2d::create_translate({m_CellPxSize * x, m_CellPxSize * y}));
                surface.fill(on_brush, m_CellFigure, nullopt, rp);
            }
            if( state == CellState::Fading  && gamma >= min_scale) {
                rp.surface_matrix(matrix_2d::create_scale({gamma, gamma}) *
                                  matrix_2d::create_translate({cell_size * beta / 2 , cell_size * beta / 2}) * 
                                  matrix_2d::create_translate({m_CellPxSize * x, m_CellPxSize * y}));
                surface.fill(fading_brush, m_CellFigure, nullopt, rp);
            }
            if( state == CellState::Emerging && beta >= min_scale ) {
                rp.surface_matrix(matrix_2d::create_scale({beta, beta}) *
                                  matrix_2d::create_translate({cell_size * gamma / 2 , cell_size * gamma / 2}) * 
                                  matrix_2d::create_translate({m_CellPxSize * x, m_CellPxSize * y}));
                surface.fill(emerging_brush, m_CellFigure, nullopt, rp);                
            }
        }
}

void GameOfLife::DrawGrid(output_surface &surface)
{
    auto rp = render_props{};
    rp.compositing(compositing_op::source);
    surface.paint(brush{rgba_color::light_gray});    
    
    auto b = brush{rgba_color::gray};
    auto sp = stroke_props{1., line_cap::none};
    auto dp = dashes{ 1.f, {1.f, 1.f} };
    
    auto pb = path_builder{};
    pb.new_figure({0.5f, 0.f});
    pb.rel_line({0.f, m_BoardHeight * m_CellPxSize});
    auto vert_line = interpreted_path{pb};
    for( auto i = 0; i < m_BoardWidth; ++i ) {
        rp.surface_matrix(matrix_2d::create_translate({i*m_CellPxSize, 0.f}));
        surface.stroke(b, vert_line, nullopt, sp, dp, rp);
    }
    
    pb.clear();
    pb.new_figure({0.f, 0.5f});
    pb.rel_line({m_BoardWidth*m_CellPxSize, 0.f});
    auto hor_line = interpreted_path{pb};
    for( auto i = 0; i < m_BoardHeight; ++i ) {
        rp.surface_matrix(matrix_2d::create_translate({0.f, i*m_CellPxSize}));
        surface.stroke(b, hor_line, nullopt, sp, dp, rp);        
    }
}

int main(int /*argc*/, char** /*argv*/)
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
