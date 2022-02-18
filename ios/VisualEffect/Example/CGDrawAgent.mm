//
//  CGDrawDemo.m
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#import "CGDrawAgent.h"
#include "CGDrawFramebuffer.h"
#include "CGDrawFilter.h"
#include "CGDrawDataInput.h"
#include "CGDrawTextureOutput.h"
#include "CGDrawDataInput.h"

#include "archiver.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace CGDraw;

@interface CGDrawAgent ()
{
    CGDrawDataInput *_dataInput;
    CGDrawFilter *_filter;
    CGDrawTextureOutput *_output;
    CGDrawFramebuffer *_framebuffer;
}
@end

@implementation CGDrawAgent

- (instancetype)init
{
    self = [super init];
    if (self) {
        _dataInput = new CGDrawDataInput();
        _filter = new CGDrawFilter();
        _output = new CGDrawTextureOutput();
        _framebuffer = new CGDrawFramebuffer();
        
        test4();
    }
    return self;
}

- (void)setInputData:(UInt8 *)data size:(CGSize)size {
    
    _dataInput->setInputData(data, size.width, size.height);
    _dataInput->addTarget(_filter);
    _filter->addTarget(_output);
    _dataInput->requestRender();
    int texId = _output->getTexId();
    CGSize textSize = CGSizeMake(_output->getTexWidth(), _output->getTexHeight());
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(glRequestRender:size:)]) {
        [self.delegate glRequestRender:texId size:textSize];
    }
}


//////////////////////////////////////////////////////////////////////////////
// Test3: polymorphism & friend
//
// Note that friendship is not necessary but make things simpler.

class Shape {
public:
    virtual ~Shape() {}
    virtual const char* GetType() const = 0;
    virtual void Print(std::ostream& os) const = 0;

protected:
    Shape() : x_(), y_() {}
    Shape(double x, double y) : x_(x), y_(y) {}

    template <typename Archiver>
    friend Archiver& operator&(Archiver& ar, Shape& s);

    double x_, y_;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, Shape& s) {
    ar.Member("x") & s.x_;
    ar.Member("y") & s.y_;
    return ar;
}

class Circle : public Shape {
public:
    Circle() : radius_() {}
    Circle(double x, double y, double radius) : Shape(x, y), radius_(radius) {}
    ~Circle() {}

    const char* GetType() const { return "Circle"; }

    void Print(std::ostream& os) const {
        os << "Circle (" << x_ << ", " << y_ << ")" << " radius = " << radius_;
    }

private:
    template <typename Archiver>
    friend Archiver& operator&(Archiver& ar, Circle& c);

    double radius_;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, Circle& c) {
    ar & static_cast<Shape&>(c);
    ar.Member("radius") & c.radius_;
    return ar;
}

class Box : public Shape {
public:
    Box() : width_(), height_() {}
    Box(double x, double y, double width, double height) : Shape(x, y), width_(width), height_(height) {}
    ~Box() {}

    const char* GetType() const { return "Box"; }

    void Print(std::ostream& os) const {
        os << "Box (" << x_ << ", " << y_ << ")" << " width = " << width_ << " height = " << height_;
    }

private:
    template <typename Archiver>
    friend Archiver& operator&(Archiver& ar, Box& b);

    double width_, height_;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, Box& b) {
    ar & static_cast<Shape&>(b);
    ar.Member("width") & b.width_;
    ar.Member("height") & b.height_;
    return ar;
}

class Canvas {
public:
    Canvas() : shapes_() {}
    ~Canvas() { Clear(); }
    
    void Clear() {
        for (std::vector<Shape*>::iterator itr = shapes_.begin(); itr != shapes_.end(); ++itr)
            delete *itr;
    }

    void AddShape(Shape* shape) { shapes_.push_back(shape); }
    
    void Print(std::ostream& os) {
        for (std::vector<Shape*>::iterator itr = shapes_.begin(); itr != shapes_.end(); ++itr) {
            (*itr)->Print(os);
            std::cout << std::endl;
        }
    }

private:
    template <typename Archiver>
    friend Archiver& operator&(Archiver& ar, Canvas& c);

    std::vector<Shape*> shapes_;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, Shape*& shape) {
    std::string type = ar.IsReader ? "" : shape->GetType();
    ar.StartObject();
    ar.Member("type") & type;
    if (type == "Circle") {
        if (ar.IsReader) shape = new Circle;
        ar & static_cast<Circle&>(*shape);
    }
    else if (type == "Box") {
        if (ar.IsReader) shape = new Box;
        ar & static_cast<Box&>(*shape);
    }
    return ar.EndObject();
}

template <typename Archiver>
Archiver& operator&(Archiver& ar, Canvas& c) {
    size_t shapeCount = c.shapes_.size();
    ar.StartArray(&shapeCount);
    if (ar.IsReader) {
        c.Clear();
        c.shapes_.resize(shapeCount);
    }
    for (size_t i = 0; i < shapeCount; i++)
        ar & c.shapes_[i];
    return ar.EndArray();
}

void test4() {
    std::string json;

    // Serialize
    {
        Canvas c;
        c.AddShape(new Circle(1.0, 2.0, 3.0));
        c.AddShape(new Box(4.0, 5.0, 6.0, 7.0));

        JsonWriter writer;
        writer & c;
        json = writer.GetString();
        std::cout << json << std::endl;
    }

    // Deserialize
    {
        Canvas c;
        JsonReader reader(json.c_str());
        reader & c;
        c.Print(std::cout);
    }
}
@end
