#pragma once
#include "Vec2.h"
#include "Mat3.h"
#include <vector>
#include "Colors.h"
#include "D3DGraphics.h"
#include "dfxlib\dl_creationadapter.h"
#include "dfxlib\dl_dxf.h"
#include <memory>

class PolyClosedLoader : DL_CreationAdapter{
public:
  PolyClosedLoader(const std::string filename){
    auto dxf = std::make_unique<DL_Dxf>();
    dxf->in(filename, this);
  }

  std::vector<const Vec2>& getVertices(){
    return vertices;
  }

  virtual void addVertex(const DL_VertexData& data) override {
    vertices.push_back({ (float)data.x, -(float)data.y });
  }

private:
  std::vector<const Vec2> vertices;
};

class Polyclosed{
public:
  Polyclosed(const std::string filename,D3DCOLOR color = YELLOW)
    :
    vertices(std::move(PolyClosedLoader(filename).getVertices())),
    color(color)
  {}
  Polyclosed(std::initializer_list<Vec2> vList, D3DCOLOR color = YELLOW)
    :
    color(color),
    vertices(vList)
  {}

  class Drawable : public ::Drawable
	{
	public:
		Drawable(const Polyclosed& parent):
		parent(parent)
		{}
		void Rasterize( D3DGraphics& gfx) const override{
			for (auto current = parent.vertices.begin(), end = parent.vertices.end() - 1; current != end; ++current)
			{
				gfx.DrawLineClipped((trans * *current), (trans * *(current + 1)), parent.color,clip);
			}
			if (parent.vertices.end() - 1 != parent.vertices.begin()){
				gfx.DrawLineClipped(trans * parent.vertices.back(), trans * parent.vertices.front(), parent.color,clip);
			}
		}
	private:
		const Polyclosed& parent;
   };
  Drawable getDrawable()const{
	  return Drawable(*this);
  }

private:
  D3DCOLOR color;
  const std::vector<const Vec2> vertices;
};