#ifndef TMX_LAYERS_H
#define TMX_LAYERS_H

#include "Layer.h"

#include "TileLayer.h"
#include "ObjectLayer.h"
#include "ImageLayer.h"

namespace tmx{

	//#added; compile-time switched noexcept specification
#ifdef _DEBUG
#define NOEXCEPT_IFNDEF_DEBUG 
#else//#ifdef _DEBUG
#define NOEXCEPT_IFNDEF_DEBUG noexcept
#endif//#ifdef _DEBUG

	//#added; explicit (but neater) cast checked in debug mode
	template <LayerType TYPE> const typename detail::LayerTypeTraits<TYPE>::type& as(const Layer& layer) NOEXCEPT_IFNDEF_DEBUG {
	#ifdef _DEBUG
	  if(layer.getType() != TYPE)
		throw std::runtime_error("Attempted invalid Layer cast!");
	#endif
	  return static_cast<const typename detail::LayerTypeTraits<TYPE>::type&>(layer);
	}
	template <LayerType TYPE> typename detail::LayerTypeTraits<TYPE>::type& as(Layer& layer) NOEXCEPT_IFNDEF_DEBUG {
	#ifdef _DEBUG
	  if(layer.getType() != TYPE)
		throw std::runtime_error("Attempted invalid Layer cast!");
	#endif
	  return static_cast<typename detail::LayerTypeTraits<TYPE>::type&>(layer);
	}
	
	//#added custom accept that accepts callable template arguments (=> lambda support)
	template <typename TILE_PRED, typename OBJ_PRED, typename IMAGE_PRED>
    void accept(const Layer& layer, const Map& map, TILE_PRED&& tile_pred, OBJ_PRED&& obj_pred, IMAGE_PRED&& image_pred){
		switch(layer.getType()){
			case LayerType::TILE:   as<LayerType::TILE>  (layer).accept(map, tile_pred ); break;
			case LayerType::OBJECT: as<LayerType::OBJECT>(layer).accept(map, obj_pred  ); break;
			case LayerType::IMAGE:  as<LayerType::IMAGE> (layer).accept(map, image_pred); break;
		}
	}

}

#endif//#ifndef TMX_LAYERS_H