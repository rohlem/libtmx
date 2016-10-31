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

}

#endif//#ifndef TMX_LAYERS_H