#include <iostream>
#include <vector>
#include <functional>
using std::array;
using std::string;
using std::cout;
using std::endl;
long long L;
unsigned long long UL;

typedef std::array<double, 12> arrd;
typedef std::array<int, 12> arri;
typedef std::array<std::string, 12> arrst;

template <typename T>
using arrtype = std::array<T, 12>;


std::vector<int> arrI(10);


//arrtype<double> gallons;
//arrtype<int> days;
//arrtype<std::string> months;

//下面这两种写法是等价的
typedef int I;
using I = int;

template <typename T>
class TYPE
{
public:
    TYPE(const T &val):v(val){}
private:
    T v;
};

//模板具体化
//TYPE<int> type1; //隐式实例化
//template class TYPE<double> type2; //显示实例化

//显示具体化
template <> class TYPE<char*>;

struct Node
{
    double item;
    Node * p_next;
};

//缩窄
double d1 {11};

//c++11不允许将宽类型转换为窄类型
//int i1 {11.00};

double f1(double, int);

//c++11
auto f2(double, int) -> double;
enum class New1 {never, somethings, ofthen, always};
enum struct New2 {never, lever, server};

class iterator
{
    Node *pt;

public:
    iterator() :pt(0){}
    iterator (Node *pn):pt(pn) {}
    double operator*() {return pt->item;}

    void Diaplay() const
    {
        std::cout << pt->item << std::endl;
    }
    iterator & operator++() //for ++it  先加后使用
    {
        pt = pt->p_next;
        return *this;
    }

    //int是为了区分 ++it和it++这两种自增方式
    iterator operator++(int) //for it++ 先使用后加所以要先保村原来的值以便返回，之后修改源pt的指向
    {
        iterator tmp = *this;
        pt = pt->p_next;
        return tmp;
    }
};

//声明指向成员函数的指针时，必须指出该函数所属的类
void (iterator::*If)() const;
//c++11函数符(类对象) using a functor
class F_mod
{
private:
    int mod;

public:
    F_mod(int d = 1):mod(d) {}
    inline bool operator ()(int x) //automatically inline
    {return x % mod == 0;}
};

double dub(double x) {return 2.0 * x;}

//typedef function<double(double)> fdd;
////包装器(适配器adapter)
//function<double(double)> ef1 = dub;

//可变参数模板 meta-operator(元运算符)
//1. 模板参数包(类型列表-Args)
//2. 函数参数包(值列表-args)
//3. 展开参数包(args...)
//4. 递归
#define SHOW

template<typename T>
void Show(const T& value)
{
    std::cout << value << "\n";
}

template<typename T, typename... Args>
#ifdef  SHOW//效率快
void Show(const T& value, const Args&... args)
#else
void Show(T value, Args... args)
#endif
{
    std::cout << value << ", ";
    Show(args...); //args展开函数包
}

//typename指出无论Bag将会是什么， Bag::value_type都将是类型的名称
template<typename Bag>
typename Bag::value_type min(const Bag & b)
{
    typename Bag::const_iterator it;
    typename Bag::value_type m = *b.begin();
    for (it = b.begin(); it != b.end(); ++it)
    {
        if (*it < m)
        {
            m = *it;
        }
    }
    return m;
}


class Point
{
public:
    Point(float xval);
    virtual ~Point();
    virtual Point& mult(float) = 0;
    virtual float x() const {}
    virtual float y() const {}
    virtual float z() const {}
    static int PonitCount();

protected:
    virtual std::ostream  print(std::ostream &os) const;
    float _x;
    static int _point_count;
};

/*
 * alignof对齐要求
 * literal operator字面量运算符
 * thread_local

 * c++11新增库
 * random
 * chrono
 * tuple<-pair
 * ratio
 * regex
 * boost/Conversion/lexical_cast
 *
 *
 *谓词：接受一个参数的布尔函数
 *二元谓词：接受两个参数的布尔函数
 */


class Point2d: public Point
{
public :
    Point2d(float x = 0.0, float y = 0.0) : Point(x), _y(y) {}
    ~Point2d() {}

    Point2d& mult(float);
    float x() const {return _x;}
    float y() const {return _y;}

    void  x(float newX) {_x = newX;}
    void  y(float newY) {_y = newY;}

    virtual float z() const {return 0.0;}
    virtual void  z(float) {}
    virtual void  operator+=(const Point2d& rhs)
    {
        _x += rhs.x();
        _y += rhs.y();
    }

protected:
    float _y;
};

//polymorphically(多态)
//inheritance from concrete class
class Point3d : public virtual Point2d
{
public :
    Point3d(float x = 0.0, float y = 0.0, float z = 0.0)
        :Point2d(x, y), _z(z)
    {}

    virtual float z() const {return _z;}
    virtual void  z(float newZ) {_z = newZ;}

#if 0
    virtual void operator += (const Point3d& rhs)
    {
        Point2d::operator +=(rhs);
        _z += rhs.z();
    }
#endif

    virtual void operator+=(const Point2d& rhs)
    {
        Point2d::operator+=(rhs);
        _z += rhs.z();
    }

    static unsigned int objectCount();

public:
    float _z;
    static Point3d origin;

};

/**
unsigned int (*)(); //normal函数指针
unsigned int (Point3d::*)(); //类成员函数指针
*/


//下属操作得到z坐标再class object中的偏移量
float Point3d::*p2 = &Point3d::_z;
float Point3d::*p1 = 0;

class Vertex : public virtual Point2d
{
public:
    //拥有virtual接口.
protected:
    Vertex *next;
};
#if 0
class Vertex3d : public Point3d, public Vertex
{
public:

protected:
    float mumble;
};
#endif

//Virtual Inheritance(虚拟继承)
//arrregation(聚合)
//encapsulation(封装)

/*2020/10/19~深度探索C++对象模型 Function语意学*/
class Base1
{
public:
    Base1();
    virtual ~Base1();
    virtual void speckClearly();
    virtual Base1 *clone() const;

protected:
    float data_Base1;
};

class Base2
{
public:
    Base2();
    virtual ~Base2();
    virtual void mumble();
    virtual Base2 *clone() const;

protected:
    float data_Base2;
};


class Derived : public Base1, public Base2
{
  public:
    Derived();
    virtual ~Derived();
    virtual Derived *clone() const;

protected:
    float data_Derived;
};

/**
  *Base2 *pbase2 = new Derived; =>>
  *Derived *temp = new Derived;
  *Base2 *pbase = temp ? temp + sizeof(Base1) : 0;
  *
  */





class Animal
{
public:
    Animal(std::string name)
    {
        m_name = name;
    }
    virtual const char* getname()
    {
        return m_name.c_str();
    }

    virtual void say()
    {
        std::cout << "this is Animal, name is " << m_name << std::endl;
    }

protected:
    std::string m_name;
};

class Cat: public Animal
{
  public:
    Cat(std::string name):Animal(name)
    {

    }

};







































