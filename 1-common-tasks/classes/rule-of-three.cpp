// The rule of three

#include <utility>

class foo
{
    public:
        foo()
            : p{ new int{5} }
        { }

        foo(const foo& other)
            : p{ new int{ *other.p } }
        { }

        foo& operator=(const foo& other)
        {
            delete p;
			p = new int{ *other.p };
            return *this;
        }

        foo(foo&& other)
        { 
            std::swap( p, other.p );
		}

        foo& operator=(foo&& other)
        {
            std::swap( p, other.p );
            return *this;
        }

        ~foo()
        {
            delete p;
        }

    private:
        int* p;
};

// Implement RAII to encapsulate and safely manage dynamically
// allocated resources.
// 
// The class `foo` dynamically allocates an `int` object in its
// constructor ([9]). To ensure that the lifetime of this `int` is
// tied to the lifetime of the `foo` object that allocated it, 
// we deallocate it in `foo`'s destructor ([34]). This idiom, known as
// [RAII](http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization),
// ensures that dynamically allocated objects are properly destroyed
// and no memory is leaked, even if an exception occurs.
// 
// We also implement a copy constructor ([12-14]), a copy assignment
// operator ([16-21]), a move constructor ([23-26]), and a move assignment 
// operator ([28-32]) to manage this resource when copying, moving, or
// assigning a `foo`. In general, if a class has any one of these functions, it
// almost certainly needs all of these functions. This idea is known
// as the *rule of five* or the *[rule of all or nothing](http://arne-mertz.de/2015/02/the-rule-of-zero-revisited-the-rule-of-all-or-nothing/)*.
// 
// Note that we can typically avoid manual memory management and
// having to write the copy constructor, assignment operator, and
// destructor entirely by using the
// [rule of zero](/common-tasks/rule-of-zero.html) and 
// [RAII classes](/common-tasks/use-raii-types.html) instead.

int main()
{
    foo f;
}
