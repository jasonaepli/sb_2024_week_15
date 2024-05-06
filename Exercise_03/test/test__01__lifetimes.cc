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

    CHECK(Tracker::sm_N_default_ctors == 1); // Default ctor is called upon instantiation of the class
    CHECK(Tracker::sm_N_copy_ctors    == 0);
    CHECK(Tracker::sm_N_move_ctors    == 0);
    CHECK(Tracker::sm_N_copy_assigns  == 0);
    CHECK(Tracker::sm_N_move_assigns  == 0);
    CHECK(Tracker::sm_N_dtors         == 0);
  }

  SECTION("scenario 2")
  {
    {
      Tracker t_1;
      Tracker t_2 = t_1;
    }

    CHECK(Tracker::sm_N_default_ctors == 1); // Default ctor is called upon instantiation of the class
    CHECK(Tracker::sm_N_copy_ctors    == 1); // Copy ctor is called when the = operator is used with a new object of the same class on the left hand side of the operand.
    CHECK(Tracker::sm_N_move_ctors    == 0);
    CHECK(Tracker::sm_N_copy_assigns  == 0); // NOTE FOR POSTERITY: There is no copy assignment, because line 74 is the construction of new object t_2.  If the new object t_2 had been constructed and THEN it was set to t_1 then the copy assignment would have incremented.
    CHECK(Tracker::sm_N_move_assigns  == 0);
    CHECK(Tracker::sm_N_dtors         == 2); // Destructor called on the original object and its copy since the assertion is made outside the scope of the objects' creation
  }

  SECTION("scenario 3")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2(t_1);
    }

    CHECK(Tracker::sm_N_default_ctors == 1); // The default constructor is called to initialize t_1.
    CHECK(Tracker::sm_N_copy_ctors    == 1); // Line 89 shows t_2 being initialized using t_1.  This matches the method signature for the copy constructor.
    CHECK(Tracker::sm_N_move_ctors    == 0);
    CHECK(Tracker::sm_N_copy_assigns  == 0);
    CHECK(Tracker::sm_N_move_assigns  == 0);
    CHECK(Tracker::sm_N_dtors         == 2); // Both t_1 and t_2 are out of scope and therefore destroyed
  }

  SECTION("scenario 4")
  {
    {
      Tracker t_1;
      Tracker t_2 = std::move(t_1);
      t_1 = Tracker();
    }

    CHECK(Tracker::sm_N_default_ctors == 2); // The default ctors are called when t_1 is first instantiated in line 103 and again when Tracker() is called and then moved to t_1 in line 105.
    CHECK(Tracker::sm_N_copy_ctors    == 0);
    CHECK(Tracker::sm_N_move_ctors    == 1); // Line 104 shows a move of t_1 being performed for the initialization of the t_2.  This results in the move constructor for t_2 being called.
    CHECK(Tracker::sm_N_copy_assigns  == 0);
    CHECK(Tracker::sm_N_move_assigns  == 1); // Line 105 is a move assignment, because the Tracker object is initialized and then moved to t_1.
    CHECK(Tracker::sm_N_dtors         == 3); // I think 3 objects are destryoed: in line 105 when unnamed object instantiated with the call to Tracker(), which is destroyed once moved to t_1, and finally once t_1, t_2, and the unnamed object are out of scope in line 106.
  }

  SECTION("scenario 5")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = std::move(t_1);
      Tracker t_3 = t_1;
    }

    CHECK(Tracker::sm_N_default_ctors == 1); // t_1 is initially created via default constructor in line 119.
    CHECK(Tracker::sm_N_copy_ctors    == 1); // A copy constructor is called in line 121 when t_3 is instantiated as a copy of t_1
    CHECK(Tracker::sm_N_move_ctors    == 1); // The move ctor is called in line 120 when t_2 is instantiated and intialized by the move from t_1
    CHECK(Tracker::sm_N_copy_assigns  == 0);
    CHECK(Tracker::sm_N_move_assigns  == 0);
    CHECK(Tracker::sm_N_dtors         == 3); // 3 objects are created: an unnamed object upon instantiation from Tracker() that is then set to the new object t_1 and destroyed and the two objects t_1 and t_3 are destroyed when out of scope.
  }

  SECTION("scenario 6")
  {
    {
      Tracker t_1 = Tracker();
      Tracker t_2 = t_1;
      t_2 = std::move(t_1);
    }

    CHECK(Tracker::sm_N_default_ctors == 1); // t_1 is initialized via default constructor in line 135
    CHECK(Tracker::sm_N_copy_ctors    == 1); // The copy constructor is called in line 136 when t_2 is initialized as a copy of t_1
    CHECK(Tracker::sm_N_move_ctors    == 0);
    CHECK(Tracker::sm_N_copy_assigns  == 0);
    CHECK(Tracker::sm_N_move_assigns  == 1); // t_1 is moved to the object named t_2 in line 137
    CHECK(Tracker::sm_N_dtors         == 2); // The unnamed object instantiated by Tracker() in line 135 is destroyed, the object t_1 is destroyed in line 137 upon completion of the move assignment.
  }
}


