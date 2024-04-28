#include <catch2/catch_test_macros.hpp>

#include <iomanip>
#include <iostream>

using namespace std;

class Tracker
{
  public:
    Tracker ()
    { sm_N_default_ctors++; }

    Tracker (Tracker const &)
    { sm_N_copy_ctors++; }
    Tracker (Tracker &&) noexcept
    { sm_N_move_ctors++; }

    Tracker & operator= ([[maybe_unused]] Tracker const & orig)
    { sm_N_copy_assigns++; return *this; }
    Tracker & operator= ([[maybe_unused]] Tracker && orig) noexcept
    { sm_N_move_assigns++; return *this; }

    ~Tracker ()
    { sm_N_dtors++; }

  public:
    static void reset_counts ()
    {
      sm_N_default_ctors = 0;
      sm_N_copy_ctors    = 0;
      sm_N_move_ctors    = 0;
      sm_N_copy_assigns  = 0;
      sm_N_move_assigns  = 0;
      sm_N_dtors         = 0;
    }

  public:
    static int32_t sm_N_default_ctors;
    static int32_t sm_N_copy_ctors;
    static int32_t sm_N_move_ctors;
    static int32_t sm_N_copy_assigns;
    static int32_t sm_N_move_assigns;
    static int32_t sm_N_dtors;
};

int32_t Tracker::sm_N_default_ctors = 0;
int32_t Tracker::sm_N_copy_ctors    = 0;
int32_t Tracker::sm_N_move_ctors    = 0;
int32_t Tracker::sm_N_copy_assigns  = 0;
int32_t Tracker::sm_N_move_assigns  = 0;
int32_t Tracker::sm_N_dtors         = 0;

TEST_CASE("lifecycle events")
{
  Tracker::reset_counts();

  SECTION("scenario 1")
  {
    Tracker t_1;

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 2")
  {
    {
      Tracker t_1;
      Tracker t_2 = t_1;
    }

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 3")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2(t_1);
    }

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 4")
  {
    {
      Tracker t_1;
      Tracker t_2 = std::move(t_1);
      t_1 = Tracker();
    }

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 5")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = std::move(t_1);
      Tracker t_3 = t_1;
    }

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }

  SECTION("scenario 6")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = t_1;
      t_2 = std::move(t_1);
    }

    CHECK(Tracker::sm_N_default_ctors == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_ctors    == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_copy_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_move_assigns  == 0); // FIX THIS AND EXPLAIN WHY
    CHECK(Tracker::sm_N_dtors         == 0); // FIX THIS AND EXPLAIN WHY
  }
}


