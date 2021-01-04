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

//����������д���ǵȼ۵�
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

//ģ����廯
//TYPE<int> type1; //��ʽʵ����
//template class TYPE<double> type2; //��ʾʵ����

//��ʾ���廯
template <> class TYPE<char*>;

struct Node
{
    double item;
    Node * p_next;
};

//��խ
double d1 {11};

//c++11������������ת��Ϊխ����
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
    iterator & operator++() //for ++it  �ȼӺ�ʹ��
    {
        pt = pt->p_next;
        return *this;
    }

    //int��Ϊ������ ++it��it++������������ʽ
    iterator operator++(int) //for it++ ��ʹ�ú������Ҫ�ȱ���ԭ����ֵ�Ա㷵�أ�֮���޸�Դpt��ָ��
    {
        iterator tmp = *this;
        pt = pt->p_next;
        return tmp;
    }
};

//����ָ���Ա������ָ��ʱ������ָ���ú�����������
void (iterator::*If)() const;
//c++11������(�����) using a functor
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
////��װ��(������adapter)
//function<double(double)> ef1 = dub;

//�ɱ����ģ�� meta-operator(Ԫ�����)
//1. ģ�������(�����б�-Args)
//2. ����������(ֵ�б�-args)
//3. չ��������(args...)
//4. �ݹ�
#define SHOW

template<typename T>
void Show(const T& value)
{
    std::cout << value << "\n";
}

template<typename T, typename... Args>
#ifdef  SHOW//Ч�ʿ�
void Show(const T& value, const Args&... args)
#else
void Show(T value, Args... args)
#endif
{
    std::cout << value << ", ";
    Show(args...); //argsչ��������
}

//typenameָ������Bag������ʲô�� Bag::value_type���������͵�����
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
 * alignof����Ҫ��
 * literal operator�����������
 * thread_local

 * c++11������
 * random
 * chrono
 * tuple<-pair
 * ratio
 * regex
 * boost/Conversion/lexical_cast
 *
 *
 *ν�ʣ�����һ�������Ĳ�������
 *��Ԫν�ʣ��������������Ĳ�������
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

//polymorphically(��̬)
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
unsigned int (*)(); //normal����ָ��
unsigned int (Point3d::*)(); //���Ա����ָ��
*/


//���������õ�z������class object�е�ƫ����
float Point3d::*p2 = &Point3d::_z;
float Point3d::*p1 = 0;

class Vertex : public virtual Point2d
{
public:
    //ӵ��virtual�ӿ�.
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

//Virtual Inheritance(����̳�)
//arrregation(�ۺ�)
//encapsulation(��װ)

/*2020/10/19~���̽��C++����ģ�� Function����ѧ*/
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







































