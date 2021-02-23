// __COPYRIGHT_START__
// Package Name : efscape
// File Name : adevs_serialization.hh
// Copyright (C) 2006-2009 by Jon C. Cline
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Bugs, comments, and questions can be sent to clinej@stanfordalumni.org
// __COPYRIGHT_END__
#ifndef ADEVS_ADEVS_SERIALIZATION_HH
#define ADEVS_ADEVS_SERIALIZATION_HH

#include <adevs.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/wrapper.hpp>

namespace boost {

  namespace serialization {

    /**
     * Free function for serialization of the adevs::Devs<X> class.
     *
     * @param ar reference to archive type
     * @param devs reference to DEVS model
     * @param version version number
     */
    template<class Archive, class X>
    void serialize(Archive & ar, adevs::Devs<X>& devs,
		   const unsigned int version)
    {
    }

    /**    
     * Free function for serialization of the adevs::Atomic<X> class.
     *
     * @param ar reference to archive type
     * @param atomic reference to ATOMIC model
     * @param version version number
     */
    template<class Archive, class X>
    void serialize(Archive & ar, adevs::Atomic<X>& atomic,
		   const unsigned int version)
    {
      // invoke serialization of the parent class
      ar & boost::serialization::make_nvp("Devs",
					  boost::serialization::base_object<adevs::Devs<X> >(atomic) );
    }

    /**
     * Free function for serialization save of the adevs::ModelWrapper<X,Y>
     * class.
     *
     * @param ar reference to archive type
     * @param wrapper reference to ModelWrapper model
     * @param version version number
     */
    template<class Archive, class ExternalType, class InternalType>
    void save(Archive & ar,
	      const adevs::ModelWrapper<ExternalType,InternalType>& wrapper,
	      const unsigned int version)
    {
      // invoke serialization save of the parent class
      ar & boost::serialization::make_nvp("Atomic",
					  boost::serialization::base_object<adevs::Atomic<ExternalType> >(wrapper) );

      // invoke serialization save of tL for wrapped model
      double tL = wrapper.getTime();
      ar & boost::serialization::make_nvp("tL", tL);

      // leave serialization of wrapped model to derived classes
    }

    /**
     * Free function for serialization load of the adevs::ModelWrapper<X,Y>
     * class.
     *
     * @param ar reference to archive type
     * @param wrapper reference to ModelWrapper model
     * @param version version number
     */
    template<class Archive, class ExternalType, class InternalType>
    void load(Archive & ar,
	      adevs::ModelWrapper<ExternalType,InternalType>& wrapper,
	      const unsigned int version)
    {
      // invoke serialization load of the parent class
      ar & boost::serialization::make_nvp("Atomic",
					  boost::serialization::base_object<adevs::Atomic<ExternalType> >(wrapper) );

      // invoke serialization load of tL for wrapped model
      double tL;
      ar & boost::serialization::make_nvp("tL", tL);
      wrapper.setTime(tL);

      // leave serialization of wrapped model to derived classes
    }

    /**
     * Free function for serialization save of the adevs::Network<X> class.
     *
     * @param ar reference to archive type
     * @param network reference to NETWORK model
     * @param version version number
     */
    template<class Archive, class X>
    void serialize(Archive & ar, adevs::Network<X>& network,
		   const unsigned int version)
    {
      // invoke serialization of the parent class
      ar & boost::serialization::make_nvp("Devs",
					  boost::serialization::base_object<adevs::Devs<X> >(network) );
    }

    /**
     * Free function for serialization save of class SimpleDigraph<X>.
     *
     * @param ar reference to archive type
     * @param digraph reference to SimpleDigraph model
     * @param version version number
     */
    template<class Archive, class X>
    void save(Archive & ar, const adevs::SimpleDigraph<X>& digraph,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<X> >(digraph) );

      //-------------------
      // 2) save sub models
      //-------------------
      // get digraph components
      typedef adevs::Devs<X> COMPONENT;
      typedef std::shared_ptr<COMPONENT> ComponentPtr;
      typedef adevs::Set<const COMPONENT*> ComponentSet;

      ComponentSet lCCp_models;
      digraph.getComponents(lCCp_models);

      // copy adevs::Set<> to std::set<>
      typedef std::set<ComponentPtr> ComponentStlSet;
      ComponentStlSet models;
      for (typename ComponentSet::iterator iter = lCCp_models.begin();
	   iter != lCCp_models.end();
	   iter++)
	models.insert(digraph.getComponent(*iter) );

      // save component models
      ar & BOOST_SERIALIZATION_NVP(models);

      //--------------------
      // 3) save model graph
      //--------------------
      // get graph
      typedef std::map< ComponentPtr, std::set<ComponentPtr> > GRAPH;
      GRAPH graph;
      digraph.getGraph(graph);

      // save graph
      ar & BOOST_SERIALIZATION_NVP(graph);

    } // serialization save of class SimpleDigraph<X>

    /**
     * Free function for serialization load of class SimpleDigraph<X>.
     *
     * @param ar reference to archive type
     * @param digraph reference to SimpleDigraph model
     * @param version version number
     */
    template<class Archive, class X>
    void load(Archive & ar, adevs::SimpleDigraph<X>& digraph,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<X> >(digraph) );

      typedef adevs::Devs<X> COMPONENT;
      typedef std::shared_ptr<COMPONENT> ComponentPtr;
      typedef std::set<ComponentPtr> ComponentStlSet;
      ComponentStlSet models;
      typedef std::map< ComponentPtr, std::set<ComponentPtr> > GRAPH;
      GRAPH graph;

      ar & BOOST_SERIALIZATION_NVP(models);
      ar & BOOST_SERIALIZATION_NVP(graph);

      // 2 add component models to digraph (note: adding shared pointers)
      for (typename ComponentStlSet::iterator iter = models.begin();
    	   iter != models.end();
    	   iter++)
    	digraph.add(*iter);

      // 3) add model couplings
      for (typename GRAPH::iterator graph_iter = graph.begin();
    	   graph_iter != graph.end(); graph_iter++) {
    	for (typename std::set<COMPONENT*>::iterator model_iter =
    	       graph_iter->second.begin();
    	     model_iter != graph_iter->second.end();
    	     model_iter++) {
      
    	  digraph.couple(graph_iter->first.get(), (*model_iter).get() );
	} // for (typename std::set...
      }	  // for (typename GRAPH::iterator...

    } // serialization load of class SimpleDigraph<X>

    /**
     * Free function for serialization of the DIGRAPH::node struct.
     *
     * @param ar reference to archive type
     * @param node reference to graph node
     * @param version version number
     */
    template<class Archive, class X, class PORT>
    void serialize(Archive & ar, typename adevs::Digraph<X,PORT>::nodeplus& node,
		   const unsigned int version)
    {
      ar & BOOST_SERIALIZATION_NVP(node.model); // serialize model
      ar & BOOST_SERIALIZATION_NVP(node.port); // serialize port
    }

    /**
     * Free function for serialization save of the Digraph class.
     *
     * @param ar reference to archive type
     * @param digraph reference to Digraph model
     * @param version version number
     */
    template<class Archive, class X, class PORT>
    void save(Archive & ar, const adevs::Digraph<X,PORT>& digraph,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      typedef adevs::PortValue<X,PORT> IO_Type;
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<IO_Type> >(digraph) );

      //-------------------
      // 2) save sub models
      //-------------------
      // get digraph components
      // * Need to convert to std containers and smart pointers for cereal
      typedef adevs::PortValue<X,PORT> IO_Type;
      typedef adevs::Devs<IO_Type> COMPONENT;
      typedef std::shared_ptr<COMPONENT> ComponentPtr;
      typedef adevs::Set<COMPONENT*> ComponentSet;

      ComponentSet lCCp_models;
      digraph.getComponents(lCCp_models);

      // copy adevs::Set<> to std::set<>
      typedef std::set<ComponentPtr> ComponentStlSet;
      ComponentStlSet models;
      for (typename ComponentSet::iterator iter = lCCp_models.begin();
	   iter != lCCp_models.end();
	   iter++) {
	ComponentPtr lCp_devs = digraph.getComponent(*iter);
	models.insert(lCp_devs);
      }

      // save component models
      ar & BOOST_SERIALIZATION_NVP(models);

      //--------------------
      // 3) save model graph
      //--------------------
      // get graph
      typedef typename adevs::Digraph<X,PORT>::nodeplus NODE;
      typedef std::map< NODE, std::set<NODE> > GRAPH;
      GRAPH graph;
      digraph.getGraph(graph);
      
      // save graph
      ar & BOOST_SERIALIZATION_NVP(graph);

    } // serialization save of class Digraph<X,Port>

    /**
     * Free function for serialization load of the Digraph class.
     *
     * @param ar reference to archive type
     * @param digraph reference to Digraph model
     * @param version version number
     */
    template<class Archive, class X, class PORT>
    void load(Archive & ar, adevs::Digraph<X,PORT>& digraph,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      typedef adevs::PortValue<X,PORT> IO_Type;
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<IO_Type> >(digraph) );
      
      // 2 add component models to digraph (note: adding shared pointers)
      typedef adevs::PortValue<X,PORT> IO_Type;
      typedef adevs::Devs<IO_Type> COMPONENT;
      typedef std::shared_ptr<COMPONENT> ComponentPtr;
      typedef std::set<ComponentPtr> ComponentStlSet;
      ComponentStlSet models;

      ar & BOOST_SERIALIZATION_NVP(models);
      
      for (typename ComponentStlSet::iterator iter = models.begin();
	   iter != models.end();
	   iter++)
	digraph.add(*iter);
      
      // 3) add model couplings
      typedef typename adevs::Digraph<X,PORT>::nodeplus NODE;
      typedef std::map< NODE, std::set<NODE> > GRAPH;
      GRAPH graph;

      ar & BOOST_SERIALIZATION_NVP(graph);

      for (typename GRAPH::iterator graph_iter = graph.begin() ;
	   graph_iter != graph.end(); graph_iter++) {
	for (typename std::set<NODE>::iterator node_iter =
	       graph_iter->second.begin();
	     node_iter != graph_iter->second.end();
	     node_iter++) {

	  digraph.couple(graph_iter->first.model.get(), graph_iter->first.port,
			 node_iter->model.get(), node_iter->port);
	} // for (typename std::set<Node>
      }	// for (typename Graph::iterator = ...

    } // serialization load of class Digraph<X,Port>

    /**
     * Free function for serialization save of the Cellspace class.
     *
     * @param ar reference to archive type
     * @param cellspace reference to Cellspace model
     * @param version version number
     */
    template<class Archive, class X>
    void save(Archive & ar, const adevs::CellSpace<X>& cellspace,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<adevs::CellEvent<X> > >(cellspace) );

      // 2) save the dimensions of the cell space
      long width = cellspace.getWidth();
      ar & BOOST_SERIALIZATION_NVP(width);

      long height = cellspace.getHeight();
      ar & BOOST_SERIALIZATION_NVP(height);

      long depth = cellspace.getDepth();
      ar & BOOST_SERIALIZATION_NVP(depth);

      //-------------------
      // 3) save sub models
      //-------------------
      // get cellspace components
      typedef adevs::Devs<adevs::CellEvent<X> > Cell;
      std::vector<const Cell*> models;

      long ll_volume = width*height*depth;
      for (int x = 0; x < width; x++) {
	for (int y = 0; y < height; y++) {
	  for (int z = 0; z < depth; z++) {
	    models.push_back(cellspace.getModel(x,y,z));
	  }
	}
      }

      // save component models
      ar & BOOST_SERIALIZATION_NVP(models);

    }

    /**
     * Free function for serialization save of the Cellspace class.
     *
     * @param ar reference to archive type
     * @param cellspace reference to Cellspace model
     * @param version version number
     */
    template<class Archive, class X>
    void load(Archive & ar, adevs::CellSpace<X>& cellspace,
	      const unsigned int version)
    {
      // 1) invoke serialization of the parent class
      ar & boost::serialization::make_nvp("NetworkModel",
					  boost::serialization::base_object<adevs::Network<adevs::CellEvent<X> > >(cellspace) );

      // 2) load the dimensions of the cell space and initialize
      long width;
      ar & BOOST_SERIALIZATION_NVP(width);

      long height;
      ar & BOOST_SERIALIZATION_NVP(height);

      long depth;
      ar & BOOST_SERIALIZATION_NVP(depth);

      cellspace.createSpace(width,height,depth);

      // 3) load component models
      typedef adevs::Devs<adevs::CellEvent<X> > Cell;
      std::vector<Cell*> models;
      ar & BOOST_SERIALIZATION_NVP(models);

      long ll_volume = width*height*depth;
      long index = 0;
      for (int x = 0; x < width; x++) {
	for (int y = 0; y < height; y++) {
	  for (int z = 0; z < depth; z++) {
	    if (index < models.size())
	      cellspace.add( models[index++], x, y, z );
	  }
	}
      }
    }

  } // namespace serialization

}   // namespace boost

#endif	// ifndef EFSCAPE_IMPL_ADEVS_SERIALIZATION_HH
