/*
 * Copyright (c) 2013-2014, Julien Bernard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef TMX_LAYER_BASE_H
#define TMX_LAYER_BASE_H

#include "Component.h"

#include <stdexcept>

namespace tmx {
  class LayerVisitor;
  class Map;

  //#added to remove dependency on virtuality to identify the type of a layer
  enum class LayerType {TILE, OBJECT, IMAGE};

  //#added forward declarations to enable them to be used as template parameters
  class TileLayer;
  class ObjectLayer;
  class ImageLayer;

  //#added to relate types with enum values
  namespace detail{
	//#typename -> LayerType
	template <typename LAYER_TYPE> struct LayerTraits;
	template <> struct LayerTraits<TileLayer>   {static constexpr LayerType layer_type = LayerType::TILE;};
	template <> struct LayerTraits<ObjectLayer> {static constexpr LayerType layer_type = LayerType::OBJECT;};
	template <> struct LayerTraits<ImageLayer>  {static constexpr LayerType layer_type = LayerType::IMAGE;};

	//#LayerType -> typename
	template <LayerType TYPE> struct LayerTypeTraits;
	template <> struct LayerTypeTraits<LayerType::TILE>   {typedef TileLayer   type;};
	template <> struct LayerTypeTraits<LayerType::OBJECT> {typedef ObjectLayer type;};
	template <> struct LayerTypeTraits<LayerType::IMAGE>  {typedef ImageLayer  type;};
  }

  /**
   * @brief A layer is a layer in the whole map.
   *
   * There are three kinds of layers: image layers, tile layers and object layers.
   */
  class Layer : public Component {
  //#changed to protected; with constructor only accessible through subclasses this class is as good as abstract
  protected:
    /**
     * @brief Layer constructor.
     */
	//#added type parameter
    Layer(const std::string& name, double opacity, bool visible, LayerType type)
      : m_name(name), m_opacity(opacity), m_visible(visible), type(type)
    {
    }

  public:
    /**
     * @brief Layer destructor.
     */
    virtual ~Layer();

    /**
     * @brief Accept function in the visitor pattern
     *
     * @param visitor the visitor
     */
    void accept(const Map& map, LayerVisitor& visitor) const;

    /**
     * @brief Get the name of the layer.
     *
     * @returns the name of the layer
     */
    const std::string& getName() const noexcept {
      return m_name;
    }

	//#added for retrieving this layer's subtype
	const LayerType& getType() const noexcept {return type;}

    /**
     * @brief Get the opacity of the layer.
     *
     * @returns the opacity of the layer (0.0 is transparent, 1.0 is opaque)
     */
    double getOpacity() const noexcept {
      return m_opacity;
    }

    /**
     * @brief Tell whether the layer is visible.
     *
     * @returns true if the layer is visible
     */
    bool isVisible() const noexcept {
      return m_visible;
    }

  private:
    const std::string m_name;
    double m_opacity;
    bool m_visible;
	//#added to remove dependency on virtuality to identify the type of a layer
	LayerType type;

  };

}


#endif // TMX_LAYER_BASE_H
