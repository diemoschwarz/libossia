#ifndef OSSIA_CPP98_HPP_2017_07_07
#define OSSIA_CPP98_HPP_2017_07_07
#include <stddef.h>
#include <ossia_export.h>
#include <string>
#include <vector>
#if (__cplusplus >= 201103L) || (defined(_MSC_VER) && (_MSC_VER >= 1900))
#define OSSIA_CPP_CXX11
#endif


namespace ossia
{
class value;
namespace net
{
class node_base;
class parameter_base;
class device_base;
}
}
/** @defgroup CPP98API C++98 API
 * C++98 bindings of libossia: a modern C++, cross-environment distributed object model for creative coding.
 *
 * ossia-cpp (Safe C++) is a simplified C++ binding, kept compatible with C++98,
 * which makes it hard to have problems at the cost of performance.
 *
 * libossia is natively written in modern C++14. The FastC++ implementation is subject to frequent updates and changes; use it instead of this binding to get maximal performance.
 *
 * libossia allows to declare the architecture of your creative coding application's functions as a tree of OSC nodes and parameters. These nodes/parameters can have attributes, which allow to declare many of their properties, such as their values, types, units, ranges, etc....
 * This OSC tree-based architecture (coined "device" in the OSSIA terminology) can then be exposed over the network under several protocols (OSCQuery only for now, for ossia-cpp), some of which allow this architecture, and the properties and values of its nodes, to be fully explored and queried.
 *
 * An illustrated documentation is available at <a href="https://ossia.github.io/?cpp--98">https://ossia.github.io/?cpp\-\-98</a>
 *
 * @{
 */

/**
 * @file ossia-cpp98.hpp
 */

/** @namespace opp is the namespace for libossia's C++98 (SafeC++ bindings)
 *
 */
namespace opp
{
/**Access modes define if the parameter's value be accessed only on read, on
 * write, or bidirectionnally
 * @brief Defines Write (Set), Read (Get) or Read/Write (Bi) access to the parameter's value
 */
enum access_mode
{
  Get, /**< only read the value */
  Set, /**< only write the value */
  Bi   /**< read and write the value */
};
/**Bounding modes define what to do at the bounds of the parameter's value
 * @brief Behaviour at the bounds of the value
 */
enum bounding_mode
{
  Free, /**< Let the value go all the way both sides over the bounds */
  Clip, /**< Clip (clamp) the values at the bounds */
  Wrap, /**< Start over at min bound when going over max bound (and vice-versa) */
  Fold, /**< Fold back value when passing over the bound */
  Low,  /**< Clip the values only on the min bound */
  High  /**< Clip the values only at the max bound */
};

class node;
class oscquery_server;
class oscquery_mirror;

//**************************************//
//               value                  //
//*************************************//

/**
 * @ingroup CPP98API
 * @brief The value class holds all ossia parameters typed values
 * @see ossia::value
 */

/**
 * @brief The value class holds all ossia parameters typed values
 * @see ossia::value
 */
class OSSIA_EXPORT value
{
  public:

    /** A container for a vector of 2 floats, supports sub-scripting
   * @brief container for a vector of 2 floats
   */
    struct vec2f {float data[2];
                  float& operator[](int i){return data[i];}};
    /** A container for a vector of 3 floats, supports sub-scripting
   * @brief container for a vector of 3 floats
     */
    struct vec3f {float data[3];
                  float& operator[](int i){return data[i];}};
    /** A container for a vector of 4 floats, supports sub-scripting
   * @brief container for a vector of 4 floats
     */
    struct vec4f {float data[4];
                  float& operator[](int i){return data[i];}};

    //*********************//
    //     Constructors    //
    //*********************//

    /**
     * @brief Value default constructors - creates an empty value
     */
    value();
    /**
     * @brief Value destructor
     */
    ~value();
    /**
     * @brief Copy constructor of a value
     * @param reference to another value
     */
    value(const value& v);
    /**
     * @brief Create a value of type int
     * @param an int
     * @see ossia::value
     */
    value(int v);
    /**
     * @brief Create a value of type bool
     * @see ossia::value
     */
    value(bool v);
    /**
     * @brief Create a value of type float
     * @see ossia::value
     */
    value(float v);
    /**
     * @brief Create a value of type double
     * @see ossia::value
     */
    value(double v);
    /**
     * @brief Create a value of type vec2f
     * @see ossia::value
     */
    value(const vec2f);
    /**
     * @brief Create a value of type vec3f
     * @see ossia::value
     */
    value(const vec3f);
    /**
     * @brief Create a value of type vec4f
     * @see ossia::value
     */
    value(const vec4f);
    /**
     * @brief Create a value of type list (vector of values)
     * @see ossia::value
     */
    value(std::vector<opp::value> v);
    /**
     * @brief Create a value of type std::string
     * @see ossia::value
     */
    value(std::string v);
    /**
     * @brief Create a value of type string (char*)
     * @see ossia::value
     */
    value(const char* v);


    //*********************//
    //     Type tests      //
    //*********************//


    /**
     * @brief Is the value of type impulse ?
     * @return True if the value is an impulse, false, otherwise
     */
    bool is_impulse() const;
    /**
     * @brief Is the value of type int ?
     * @return True if the value is an int, false, otherwise
     */
    bool is_int() const;
    /**
     * @brief Is the value of type float?
     * @return True if the value is a float, false, otherwise
     */
    bool is_float() const;
    /**
     * @brief Is the value of type boolean ?
     * @return True if the value is a boolean, false, otherwise
     */
    bool is_bool() const;
    /**
     * @brief Is the value of type vec2f ?
     * @return True if the value is a vec2f, false, otherwise
     */
    bool is_vec2f() const;
    /**
     * @brief Is the value of type vec3f ?
     * @return True if the value is a vec3f, false, otherwise
     */
    bool is_vec3f() const;
    /**
     * @brief Is the value of type vec4f ?
     * @return True if the value is a vec4f, false, otherwise
     */
    bool is_vec4f() const;
    /**
     * @brief Is the value of type list?
     * @return True if the value is a list, false, otherwise
     */
    bool is_list() const;
    /**
     * @brief Is the value of type string?
     * @return True if the value is a string, false, otherwise
     */
    bool is_string() const;


    //*********************//
    //     Convertors      //
    //*********************//

    /**
     * @brief converts the value to an int
     * @return value converted to int
     */
    int to_int() const;
    /**
     * @brief converts the value to a float
     * @return value converted to float
     */
    float to_float() const;
    /**
     * @brief converts the value to a boolean
     * @return value converted to boolean
     */
    bool to_bool() const;
    /**
     * @brief converts the value to a vec2f
     * @return value converted to vec2f
     */
    vec2f to_vec2f() const;
    /**
     * @brief converts the value to a vec3f
     * @return value converted to vec3f
     */
    vec3f to_vec3f() const;
    /**
     * @brief converts the value to a vec4f
     * @return value converted to vec4f
     */
    vec4f to_vec4f() const;
    /**
     * @brief converts the value to a list (vector of opp::value)
     * @return value converted to list (vector of opp::value)
     */
    std::vector<opp::value> to_list() const;
    /**
     * @brief converts the value to a string
     * @return value converted to std::string
     */
    std::string to_string() const;

    //*********************//
    //Assignment Operators //
    //*********************//

    /**
     * @brief operator = assigns with another opp::value
     * @param v : an opp::value
     * @return the reference to this value object
     */
    value& operator=(const value& v);
    /**
     * @brief operator = assigns with an integer
     * @param v : an int
     * @return the reference to this value object
     */
    value& operator=(int v);
    /**
     * @brief operator = assigns with a float
     * @param v : a float
     * @return the reference to this value object
     */
    value& operator=(float v);
    /**
     * @brief operator = assigns with a bool
     * @param v : a bool
     * @return the reference to this value object
     */
    value& operator=(bool v);
    /**
     * @brief operator = assigns with a vec2f
     * @param v : a vec2f
     * @return the reference to this value object
     */
    value& operator=(vec2f v);
    /**
     * @brief operator = assigns with a vec3f
     * @param v : a vec3f
     * @return the reference to this value object
     */
    value& operator=(vec3f v);
    /**
     * @brief operator = assigns with a vec4f
     * @param v : a vec4f
     * @return the reference to this value object
     */
    value& operator=(vec4f v);
    /**
     * @brief operator = assigns with a vector of values (aka list)
     * @param v : a vector of values (aka list)
     * @return the reference to this value object
     */
    value& operator=(std::vector<opp::value> v);
    /**
     * @brief operator = assigns with a string
     * @param v : a string
     * @return the reference to this value object
     */
    value& operator=(std::string v);

    /**
     * @brief sets the value as an impulse (a value-less signal)
     */
    void set_impulse();
    /**
     * @brief sets the value as an int
     * @param v int is moved intoto the value object
     */
    void set_int(int v);
    /**
     * @brief sets the value as a float
     * @param v float is moved intoto the value object
     */
    void set_float(float v);
    /**
     * @brief sets the value as a bool
     * @param v bool is moved intoto the value object
     */
    void set_bool(bool v);
    /**
     * @brief sets the value as a vec2f
     * @param v vec2f is moved intoto the value object
     */
    void set_vec2f(vec2f v);
    /**
     * @brief sets the value as a vec3f
     * @param v vec3f is moved intoto the value object
     */
    void set_vec3f(vec3f v);
    /**
     * @brief sets the value as a vec4f
     * @param v vec4f is moved intoto the value object
     */
    void set_vec4f(vec4f v);
    /**
     * @brief sets the value as a vector of opp::values
     * @param v vector of opp::values is moved intoto the value object
     */
    void set_list(std::vector<opp::value> v);
    /**
     * @brief sets the value as a string
     * @param v string is moved intoto the value object
     */
    void set_string(std::string v);

#if defined(OSSIA_CPP_CXX11)
    value(value&& v);
    value& operator=(value&& v);
#endif
  private:
    friend class node;
    value(const ossia::value& v);
    template<typename T>
    value(const T* v);
    ossia::value* m_val;
};

/** @brief container for a value callback
 * @see opp::callback_index
 */
typedef void (*value_callback)(void*, const opp::value&);
/** @brief container for a connection callback
 * @see opp::osquery_server::set_connection_callback
 */
typedef void (*connection_callback)(void*, const std::string&);
/** @brief container for a disconnection callback
 * @see opp::osquery_server::set_disconnection_callback
 */
typedef void (*disconnection_callback)(void*, const std::string&);

/**
 * @ingroup CPP98API
 * @brief The callback_index struct holds callbacks for adding listeners to parameters' values
*/
struct OSSIA_EXPORT callback_index {
    callback_index();
    ~callback_index();
    callback_index(const callback_index&);
    callback_index& operator=(const callback_index&);
    operator bool() const;

  private:
    friend class node;

    struct impl;
    impl* index;
};


/**The nodes in the device are simply called "nodes" in the API. Nodes are identified with the OSC syntax: /foo/bar.
 * Nodes per se don't carry any value; they have to be extended with parameters to be able to send and receive messages.
 * When multiple nodes with the same name are created, they will be appended instance numbers, separated with a dot.
 * E.g. when duplicating the node /foo, its duplicates will be named /foo.1, /foo.2, etc…
 * This allows to have a cleaner representation of the address/namespace.
 * [Namespace using slashes for instances](https://ossia.github.io/images/NamespaceSlash.png)
 * [Namespace using dots for instances](https://ossia.github.io/images/NamespaceDot.png)
 * @ingroup CPP98API
 * @brief The node class holds all ossia nodes and their optional parameters
 * @see ossia::value
*/
class OSSIA_EXPORT node
{
  public:

    //*********************//
    //     Constructors    //
    //*********************//

    /**
     * @brief node default constructor
     */
    node();
    /**
     * @brief node copy constructor
     */
    node(const node&);
    /**
     * @brief assign the current node to another one
     * @return reference to the assigned node
     */
    node& operator = (const node&);

    /**
     * @brief node default destructor
     */
    ~node();

    /**
     * @brief checks is the node is valid
     * @return true if the node is valid
     */
    operator bool() const;

    /**
     * @brief get a node's name
     * @return a string with the node's name
     */
    std::string get_name() const;
    /**
     * @brief set or change a node's name
     * @param a string with the desired node name
     */
    void set_name(std::string s);

    /**
     * @brief does this node have a parameter ?
     * @return true if there is a parameter to this node
     */
    bool has_parameter() const;

    /**
     * @brief get this node's OSC address
     * @return this node's OSC address as a string
     */
    std::string get_address() const;
    /**
   * @brief return all children recursively by priority order
   * @return a vector of opp::node
   */
    std::vector<node> get_namespace() const;
    /**
   * @brief returns all direct children (one level of hierarchy only)
   * @return a vector of opp::node
   */
    std::vector<node> get_children() const;
    /**
     * @brief finds a child node by its name
     * @param addr is a string corresponding to the desired child node's name
     * @return the child node
     */
    node find_child(std::string addr);
    /**
     * @brief removes a child node, described by its name
     * @param addr a string corresponding to the child node's name that one wants to remove
     */
    void remove_child(std::string addr);
    /**
     * @brief removes all children of the current node
     */
    void remove_children();

    /**
     * @brief creates a child node to the current node
     * this creates a "container", without a parameter,
     * which can later be added with the set_(type) methods below
     * @param addr is a string to use as the child's node name
     * @return the just-created node object
     */
    node create_child(std::string addr);

    /**Impulse: no value; just a message.
     * @brief adds an impulse parameter to the current node
     */
    void set_impulse();
    /**Integer: 32-bit int.
     * @brief adds an int parameter to the current node
     */
    void set_int();
    /**Floating-point: 32-bit float.
     * @brief adds a float parameter to the current node
     */
    void set_float();
    /**Boolean: true/false.
     * @brief adds a bool parameter to the current node
     */
    void set_bool();
    /**Vec2f:  As an optimisation, vec2f is a specific type for 2 floats
     * @brief adds a vec2f parameter to the current node
     */
    void set_vec2f();
    /**Vec3f: As an optimisation, vec3f is a specific type for 3 floats
     * @brief adds a vec3f parameter to the current node
     */
    void set_vec3f();
    /**Vec4f: As an optimisation, vec4f is a specific type for 4 floats
     * @brief adds a vec4f parameter to the current node
     */
    void set_vec4f();
    /**List: : a generic list of values: [3, 'a', 2.68, ["foo", "bar"]]
     * @brief adds a list parameter to the current node
     */
    void set_list();
    /**String: a string of chars as defined  in the C++ standard library
     * @brief adds a string parameter to the current node
     */
    void set_string();
    /**Generic buffer : when a string should be interpreted as a a raw binary blob.
     * @brief adds a buffer parameter to the current node
     */
    void set_buffer();
    /**File path : used for when a string is a filesystem path, like /home/self/sound.wav or c:\\document.txt
     * @brief adds a filepath parameter to the current node
     */
    void set_filepath();
    /**RGB: 3 float numbers between 0. and 1. describing respectively Red, Green and Blue color values
     * @brief adds a vec3f parameter to the current node, with the color.rgb unit
     */
    void set_rgb();
    /**RGBA: 4 float numbers between 0. and 1. describing respectively Red, Green, Blue and Alpha color values
     * @brief adds a vec4f parameter to the current node, with the color.rgba unit
     */
    void set_rgba();
    /**ARGB: 4 float numbers between 0. and 1. describing respectively Alpha, Red, Green and Blue color values
     * @brief adds a vec4f parameter to the current node, with the color.argb unit
     */
    void set_argb();
    /**8 bits ARGB: 4 int numbers between 0 and 255 describing respectively Alpha, Red, Green and Blue color values
     * @brief adds a vec4f parameter to the current node, with the color.argb8 unit
     */
    void set_argb8();
    /**HSV: 3 float numbers between 0. and 1. describing respectively Hue, Saturation and Value (Luminosity) color values in the HSV colorspace
     * @brief adds a vec3f parameter to the current node, with the color.hsv unit
     */
    void set_hsv();
    /**Cart2D: Cartesian 2-dimensional position (i.e. X, Y)
     * @brief adds a vec2f parameter to the current node, with the position.cart2D unit
     */
    void set_cart2D();
    /**Cart3D: Cartesian 3-dimensional position (ie. X, Y, Z)
     * @brief adds a vec3f parameter to the current node, with the position.cart3D unit
     */
    void set_cart3D();
    /**OpenGL: Cartesian 3-dimensional position (ie. X, Y, Z) in the OpenGL coordinate reference system
     * @brief adds a vec3f parameter to the current node, with the position.openGL unit (aka X, Y, Z)
     */
    void set_opengl();
    /**Polar: Polar 2-dimensional position (ie. ad: amplitude, distance)
     * @brief adds a vec2f parameter to the current node, with the position.polar unit
     */
    void set_polar();
    /**Spherical: Polar 3-dimensional position (ie. aed: amplitude, elevation, distance)
     * @brief adds a vec3f parameter to the current node, with the position.spherical unit (aka aed)
     */
    void set_spherical();
    /**Cylindrical: Mixed 3-dimensional position (ie. daz: distance, amplitude, Z)
     * @brief adds a vec3f parameter to the current node, with the position.cylindrical unit (aka daz)
     */
    void set_cylindrical();

    /**radian: a angle expressed in radian
     * @brief cadds a vec3f parameter to the current node, with the angle.radian unit
     */
    void set_angle_radian();
    /**degree: a angle expressed in degrees
     * @brief adds a vec3f parameter to the current node, with theangle.radian unit
     */
    void set_angle_degree();
    /**Quaternion: An extension of the complex numbers for 3D orientation, in the form a+bi+cj+dk
     * @brief adds a vec4f parameter to the current node, with the orientation.quaternion unit
     */
    void set_quaternion();
    /**Euler: A triplet of angles (in degrees) describing the orientation of a rigid body with respect to a fixed coordinate system
     * @brief adds a vec3f parameter to the current node, with the orientation.euler unit (aka Euler angles)
     */
    void set_euler();
    /**Axis: An angle (a, in degrees) relative to a 3-dimensional vector, expressed in the order X, Y, Z, a
     * @brief adds a vec4f parameter to the current node, with the orientation.axis unit
     */
    void set_axis();
    /**deciBel: a single float value expressed in a logarithmic scale, typically to describe an audio gain (0dB being the nominal gain, <0dB describing a signal attenuation)
     * @brief adds a float parameter to the current node, with the gain.decibel unit
     */
    void set_decibel();
    /**midigain: a value in the [0 127] range mimicing a MIDI gain controller. 100 for the nominal level, 127 for +12dB
     * @brief adds a float parameter to the current node, with the gain.midigain unit
     */
    void set_midigain();
    /**linear: a linear gain in the [0. 1.) range, with 1. being the nominal level
     * @brief adds a float parameter to the current node, with the gain.linear unit
     */
    void set_linear();
    /**frequency: a frequency expressed in Hertz
     * @brief adds a float parameter to the current node, with the time.frequency unit
     */
    void set_frequency();
    /**midi_pitch: a frequency expressed as a MIDI pitch (ie. 36 for C3)
     * @brief adds a float parameter to the current node, with the time.midi_pitch unit
     */
    void set_midi_pitch();
    /**bpm: a frequency expressed in beats per minute
     * @brief adds a float parameter to the current node, with the time.bpm unit
     */
    void set_bpm();


    /**Impulse: no value; just a message.
     * @brief creates a child node with tne given name, and an impulse parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_impulse(std::string addr);
    /**Integer: 32-bit int.
     * @brief creates a child node with tne given name, and an int parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_int(std::string addr);
    /**Floating-point: 32-bit float.
     * @brief creates a child node with tne given name, and a float parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_float(std::string addr);
    /**Boolean: true/false.
     * @brief creates a child node with tne given name, and a bool parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_bool(std::string addr);
    /**Vec2f: As an optimisation, vec2f is a specific type for 2 floats
     * @brief creates a child node with tne given name, and a vec2f parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_vec2f(std::string addr);
    /**Vec3f: As an optimisation, vec3f is a specific type for 3 floats
     * @brief creates a child node with tne given name, and a vec3f parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_vec3f(std::string addr);
    /**Vec4f: As an optimisation, vec4f is a specific type for 4 floats
     * @brief creates a child node with tne given name, and a vec4f parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_vec4f(std::string addr);
    /**List: : a generic list of values: [3, 'a', 2.68, ["foo", "bar"]]
     * @brief creates a child node with tne given name, and a list parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_list(std::string addr);
    /**String: a string of chars as defined in the C++ standard library
     * @brief creates a child node with tne given name, and a string parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_string(std::string addr);
    /**Generic buffer : when a string should be interpreted as a a raw binary blob.
     * @brief creates a child node with tne given name, and a buffer parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_buffer(std::string addr);
    /**File path : used for when a string is a filesystem path, like /home/self/sound.wav or c:\\document.txt
     * @brief creates a child node with tne given name, and a filepath parameter
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_filepath(std::string addr);
    /**RGB: 3 float numbers between 0. and 1. describing respectively Red, Green and Blue values
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the color.rgb unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_rgb(std::string addr);
    /**RGBA: 4 float numbers between 0. and 1. describing respectively Red, Green, Blue and Alpha values
     * @brief creates a child node with tne given name,
     * and a vec4f parameter with the color.rgba unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_rgba(std::string addr);
    /**ARGB: 4 float numbers between 0. and 1. describing respectively Alpha, Red, Green and Blue values
     * @brief creates a child node with tne given name,
     * and a vec4f parameter with the color.argb unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_argb(std::string addr);
    /**8 bits ARGB: 4 int numbers between 0 and 255 describing respectively Alpha, Red, Green and Blue values
     * @brief creates a child node with tne given name,
     * and a vec4f parameter with the color.argb8 unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_argb8(std::string addr);
    /**HSV:  3 float numbers between 0. and 1. describing respectively Hue, Saturation and Value (Luminosity) values in the HSV colorspace
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the color.hsv unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_hsv(std::string addr);
    /**Cart2D: Cartesian 2-dimensional position (i.e. X, Y)
     * @brief creates a child node with tne given name,
     * and a vec2f parameter with the position.cart2D unit (aka xy)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_cart2D(std::string addr);
    /**Cart3D: Cartesian 3-dimensional position (ie. X, Y, Z)
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the position.cart3D unit (aka XYZ)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_cart3D(std::string addr);
    /**OpenGL: Cartesian 3-dimensional position (ie. X, Y, Z) in the OpenGL coordinate reference system
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the position.openGL unit (aka xyz)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_opengl(std::string addr);
    /**Polar: Polar 2-dimensional position (ie. ad: amplitude, distance)
     * @brief creates a child node with tne given name,
     * and a vec2f parameter with the position.polar unit (aka ad)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_polar(std::string addr);
    /**Spherical: Polar 3-dimensional position (ie. aed: amplitude, elevation, distance)
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the position.spherical unit (aka aed)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_spherical(std::string addr);
    /**Cylindrical: Mixed 3-dimensional position (ie. daz: distance, amplitude, Z)
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the position.cylindrical unit (aka daz)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_cylindrical(std::string addr);

    /**radian: a angle expressed in radian
     * @brief creates a child node with tne given name,
     * and a float parameter with the angle.radian unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_angle_radian(std::string addr);
    /**radian: a angle expressed in degrees
     * @brief creates a child node with tne given name,
     * and a float parameter with the angle.radian unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_angle_degree(std::string addr);

    /**Quaternion: An extension of the complex numbers for 3D orientation, in the form a+bi+cj+dk
     * @brief creates a child node with tne given name,
     * and a vec4f parameter with the orientation.quaternion unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_quaternion(std::string addr);
    /**Euler: A triplet of angles (in degrees): {yaw, pitch, roll} describing the orientation of a rigid body with respect to a fixed coordinate system
     * @brief creates a child node with tne given name,
     * and a vec3f parameter with the orientation.euler unit (aka Euler angles)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_euler(std::string addr);
    /**Axis: An angle (w, in degrees) relative to a 3-dimensional vector, expressed in the order X, Y, Z, w
     * @brief creates a child node with tne given name,
     * and a vec4f parameter with the orientation.axis unit (aka xyza)
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_axis(std::string addr);
    /**deciBel: a single float value expressed in a logarithmic scale, typically to describe an audio gain (0dB being the nominal gain, <0dB describing a signal attenuation)
     * @brief creates a child node with tne given name,
     * and a float parameter with the gain.decibel unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_decibel(std::string addr);
    /**midigain: a value in the [0 127] range mimicing a MIDI gain controller. 100 for the nominal level, 127 for +12dB
     * @brief creates a child node with tne given name,
     * and a float parameter with the gain.midigain unit in the [0 127) range
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_midigain(std::string addr);
    /**linear: a linear gain in the [0. 1.) range, with 1. being the nominal level
     * @brief creates a child node with tne given name,
     * and a float parameter with the gain.linear unit in the [0. 1.) range
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_linear(std::string addr);
    /**frequency: a frequency expressed in Hertz
     * @brief creates a child node with tne given name,
     * and a float parameter with the time.frequency unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_frequency(std::string addr);
    /**midi_pitch: a frequency expressed as a MIDI pitch (ie. 36 for C3)
     * @brief creates a child node with tne given name,
     * and a float parameter with the time.midi_pitch unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_midi_pitch(std::string addr);
    /**bpm: a frequency expressed in beats per minute
     * @brief creates a child node with tne given name,
     * and a float parameter with the time.bpm unit
     * @param addr: the name of the created node
     * @return the created opp::node object
     */
    node create_bpm(std::string addr);

    /**
     * @brief set the node's parameter's value
     * @param v an opp:value
     * @return a reference to this node
     * @see opp::value
     */
    node& set_value(opp::value v);
    /**
     * @brief get this node's (local) parameter's value
     * @return an opp::value with this node's parameter's value
     */
    opp::value get_value() const;
    /**
     * @brief fetch this node's parameter's value over the network:
     * @return an opp::value with this node's parameter's value
     * @see opp::oscquery_mirror
     */
    opp::value fetch_value() const;
    /**
     * @brief sets a callback allowing to listen to this value
     * @param c a value_callback
     * @param ctx the context as a void*
     * @return a callback_index struct
     * @see opp::value_callback
     * @see opp::callback_index
     */
    callback_index set_value_callback(value_callback c, void* ctx);
    /**
     * @brief removes a value_callback, previously set with set_value_callback()
     * @param idx a callback_index, as returned by set_value_callback()
     * @see opp::callback_index
     */
    void remove_value_callback(callback_index idx);
    /**
     * @brief sets the 'min' attribute of this node's parameter (minimum value)
     * @param min an opp::value with the desired minimum value
     * @return a reference to this node
     * @see opp::node::set_bounding
     */
    node& set_min(opp::value min);
    /**
     * @brief gets the 'min' attribute of this node's parameter (minimum value)
     * @return an opp::value with this node's parameter's minimum value
     * @see opp::node::get_bounding
     */
    opp::value get_min() const;
    /**
     * @brief sets the 'max' attribute of this node's parameter (maximum value)
     * @param min an opp::value with the desired mmaximum value
     * @return a reference to this node
     *  @see opp::node::set_bounding
     */
    node& set_max(opp::value max);
    /**
     * @brief gets the 'max' attribute of this node's parameter (maximum value)
     * @return an opp::value with this node's parameter's maximum value
     * @see opp::node::get_bounding
     */
    opp::value get_max() const;
    /**
     * @brief sets a list of the values accepted by this node's parameter ("values" attribute)
     * @param v a vector of opp::value with the desired list of accepted values
     * @return a reference to this node
     * @see opp::node::set_bounding
     */
    node& set_accepted_values(std::vector<opp::value> v);
    /**
     * @brief gets a list of the values accepted by this node's parameter ("values" attribute)
     * @return a vector of opp::value with the list of this node's parameter's accepted values
     */
    std::vector<opp::value> get_accepted_values() const;
    /**
     * @brief sets the unit attribute of this node's parameter
     * @param v a string with this unit's name
     * @return a reference to this node
     * @see ossia::unit_t
     */
    node& set_unit(std::string v);
    /**
     * @brief gets the unit of this node's parameter
     * @return a string with this node's parameter's unit name
     * @see ossia::unit_t
     */
    std::string get_unit() const;
    /**
     * @brief sets the access_mode attribute of this node's parameter
     * @param v an opp::access_mode of the chosen mode
     * @return a reference to this node
     */
    node& set_access(access_mode v);
    /**
     * @brief gets the access_mode attribute of this node's parameter
     * @return an opp::access_mode with this node's parameter's access mode
     */
    access_mode get_access() const;
    /**
     * @brief sets the bounding_mode attribute of this node's parameter
     * @param v an opp::bounding_mode of the chosen mode
     * @return a reference to this node
     */
    node& set_bounding(bounding_mode v);
    /**
     * @brief gets the bounding_mode attribute of this node's parameter
     * @return an opp::bounding_mode with this node's parameter's access mode
     */
    bounding_mode get_bounding() const;

    /**
     * @brief sets the repetition_filter attribute of this node's parameter
     * @param v an bool: true to filter out this node's parameter's value repetitions
     * @return a reference to this node
     */
    node& set_repetition_filter(bool v);
    /**
     * @brief gets the repetition_filter attribute of this node's parameter
     * @return a bool: true if this node's parameter's value repetitions are filtered out
     */
    bool get_repetition_filter() const;

    /**
     * @brief sets the default_value attribute of this node's parameter
     * @param v an opp::value with this node's parameter's default value
     * @return a reference to this node
     * @see ossia::unit_t
     */
    node& set_default_value(value v);
    /**
     * @brief gets the default_value attribute of this node's parameter
     * @return an opp::value with this node's parameter's default value
     */
    value get_default_value();
    /**
     * @brief sets this node's description attribute
     * @param v a string with the textual description of this node
     * @return a reference to this node
     */
    node& set_description(std::string v);
    /**
     * @brief gets this node's description attribute
     * @return a string with the textual description of this node
     */
    std::string get_description() const;
    /**
     * @brief sets his node's tags attribute
     * @param v a vector of strings with the desired tags of this node'
     * @return a reference to this node
     */
    node& set_tags(std::vector<std::string> v);
    /**
     * @brief gets this node's tags attribute
     * @return a string with this node's tags
     */
    std::vector<std::string> get_tags() const;

    /**
     * @brief sets how many instances this node can have
     * @param min the minimum number of instances this node can have
     * @param max the maximum number of instances this node can have
     * @return a reference to this node
     */
    node& set_instance_bounds(int min, int max);
    /**
     * @brief unset how many instances this node can have
     * @return a reference to this node
     */
    node& unset_instance_bounds();
    /**
     * @brief gets how many instances this node can have
     * @return a std::pair with the minimum and maxium number sof instances this node can have
     */
    std::pair<int, int> get_instance_bounds() const;

    /**
     * @brief sets the priority attribute of this node's parameter
     * @param v a float with this node's parameter's priority value (higher numbers for higher priorities)
     * @return a reference to this node
     */
    node& set_priority(float v);
    /**
     * @brief unsets the priority attribute of this node's parameter
     * @return a reference to this node
     */
    node& unset_priority();
    /**
     * @brief gets the priority attribute of this node's parameter
     * @return a float with this node's parameter's priority value (higher numbers for higher priorities)
     */
    float get_priority();

    /**An optional value that says how often a value should be updated.
     * @brief sets the refresh_rate attribute of this node's parameter
     * @param v an int with this node's parameter's refresh_rate value
     * @return a reference to this node
     */
    node& set_refresh_rate(int v);
    /**
     * @brief unsets the refresh_rate attribute of this node's parameter
     * @return a reference to this node
     */
    node& unset_refresh_rate();
    /**
     * @brief gets the refresh_rate attribute of this node's parameter
     * @return a float with this node's parameter's refresh_rate value
     */
    int get_refresh_rate();

    /**An optional value that says by which increment a value should change, for instance in a value editor.
     * @brief sets the value_step_size attribute of this node's parameter
     * @param v the increment size
     * @return a reference to this node
     */
    node& set_value_step_size(double v);
    /**
     * @brief unsets the value_step_size attribute of this node's parameter
     * @return a reference to this node
     */
    node& unset_value_step_size();
    /**
     * @brief gets the value_step_size attribute of this node's parameter
     * @return a float with this node's parameter's refresh_rate value
     */
    double get_value_step_size();

    /**
     * @brief sets this node's hidden attribute
     * @param v a bool: true to hide this node
     * @return a reference to this node
     */
    node& set_hidden(bool v);
    /**
     * @brief gets this node's hidden attribute
     * @return a bool: true if the node is hidden
     */
    bool get_hidden() const;

    /**
     * @brief sets the disabled attribute of this node's parameter
     * @param v a bool: true to disable this node's parameter
     * @return a reference to this node
     */
    node& set_disabled(bool v);
    /**
     * @brief gets the disabled attribute of this node's parameter
     * @return a bool: true if the node's parameter is disabled
     */
    bool get_disabled() const;

    /**
     * @brief sets the muted attribute of this node's parameter
     * @param v a bool: true to mute this node's parameter
     * @return a reference to this node
     */
    node& set_muted(bool v);
    /**
     * @brief gets the muted attribute of this node's parameter
     * @return a bool: true if the node's parameter is muted
     */
    bool get_muted() const;


    /**
     * @brief sets the critical attribute of this node's parameter
     * @param v a bool: true to mark this node's parameter  as critical
     * @return a reference to this node
     */
    node& set_critical(bool v);
    /**
     * @brief gets the critical attribute of this node's parameter
     * @return a bool: true if the node's parameter  is critical
     */
    bool get_critical() const;

    /**
     * @brief gets the zombie attribute of this node's parameter
     * @return a bool: true if the node has been zombified
     */
    bool get_zombie() const;


#if defined(OSSIA_CPP_CXX11)
    node(node&&) = default;
    node& operator=(node&&) = default;
#endif

  private:
    friend class oscquery_mirror;
    friend class oscquery_server;
    node(ossia::net::node_base* b);
    node(ossia::net::node_base* b, ossia::net::parameter_base* addr);
    void init();
    void cleanup(const ossia::net::node_base&);
    void cleanup_parameter(const ossia::net::parameter_base&);

    ossia::net::node_base* m_node;
    ossia::net::parameter_base* m_param;
};


/**A device represents a tree of parameters.
 * Local devices map to real parameters on the executable libossia is used with. For instance the frequency of a filter, etc.
 * Devices can be mapped to different protocols: OSC, OSCQuery, Midi, etc.
 * For the sake of simplicity, the safeC++ (opp) binding ties together device and protocol implementation
 * We use the OSCQuery protocol here.
 * Once a device has been created, it is possible to check what's in it by going to http://localhost:5678.
 * For more information on the OSCQuery protocol, please refer to the proposal.
 *
 * @ingroup CPP98API
 * @brief The oscquery_server class allows to create a local OSCQuery server
 */
class OSSIA_EXPORT oscquery_server
{
  public:
    /** A server can be created without arguments.
     * It will then have to be configured later on with
     * opp::oscquery_server::setup
     * @brief declares a (yet to be configured) OSCQuery server
     */
    oscquery_server();
    /**
     * @brief declares and configures an OSCQuery server
     * @param name the name of the OSCQuery server
     * @param oscPort the OSC port to receive messages from (defaults to 1234)
     * @param wsPort the websocket port the server uses to manage queries (defaults to 5678)
     */
    oscquery_server(std::string name, int oscPort = 1234, int wsPort = 5678);
    /**
     * @brief OSCQuery Server default destructor
     */
    ~oscquery_server();
    /**
     * @brief sets up an OSCQuery Server with the appropriate device name and ports
     * @param name the name of the OSCQuery server
     * @param oscPort the OSC port to receive messages from (defaults to 1234)
     * @param wsPort the websocket port the server uses to manage queries (defaults to 5678)
     */
    void setup(std::string name, int oscPort = 1234, int wsPort = 5678);
    /**
     * @brief get this server's root opp::node
     * @return this server's root opp::node
     */
    node get_root_node() const;

    /**
     * @brief set a callback to be called when a connection is made to this device
     * @param c the connection_callback
     * @param ctx the callback context as a void*
     */
    void set_connection_callback(connection_callback c, void* ctx);
    /**
     * @brief remove the previously set connection_callback
     */
    void remove_connection_callback();

    /**
     * @brief set a callback to be called when a connection to this device is closed
     * @param c the connection_callback
     * @param ctx the callback context as a void*
     */
    void set_disconnection_callback(disconnection_callback c, void* ctx);
    /**
     * @brief remove the previously set disconnection_callback
     */
    void remove_disconnection_callback();

  private:
    void on_connection(const std::string&);
    void on_disconnection(const std::string&);
    ossia::net::device_base* m_dev;
    connection_callback m_con;
    void* m_con_ctx;
    disconnection_callback m_discon;
    void* m_discon_ctx;
};

/**Remote devices are mirror images of local devices on other applications: remote controls, mobile apps, etc. Every parameter in a local device will be synchronized with the remote devices that connected to it.
 * @ingroup CPP98API
 * @brief The oscquery_mirror class allows to create a mirror image of a remote OSCQuery server
 */
class OSSIA_EXPORT oscquery_mirror
{
  public:
    /**
     * @brief create an OSCQuery mirror device and connect it to a remote device
     * @param name the name of the remote device (server)
     * @param host the IP of the remote device (server)
     */
    oscquery_mirror(std::string name, std::string host = "ws://127.0.0.1:5678");
    /**
     * @brief OSCQuery Mirror default destructor
     */
    ~oscquery_mirror();

    /**
     * @brief get this server's root opp::node
     * @return this server's root opp::node
     */
    node get_root_node() const;
    /**
     * @brief refresh the Mirror's namespace
     */
    void refresh();
    /**
     * @brief reconnect to the remote device
     * @param name the name of the remote device (server)
     * @param host the IP of the remote device (server)
     */
    void reconnect(std::string name, std::string host);

  private:
    ossia::net::device_base* m_dev;
};
}

/** @}*/

#endif



