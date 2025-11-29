#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <map>
#include <iostream>

template <class T>
class Vertex {
	private:
		int id;									// vertex key
		std::map<int, int> connectedTo;			// list of neighbors ids and edge weights
		T payload;								// add payload here

	public:
		Vertex() { this->id = 0; }				// default constructor

		Vertex(int key, T pl) {					// constructor with key and payload
			this->id 	  = key;				// set key
			this->payload = pl;					// set payload
		}

		T getPayload(){ return this->payload; }	// get payload

		void addNeighbor(int nbr, int weight = 0) {						// adds neighbor
			connectedTo[nbr] = weight;									// if neighbor exists the weight will be updated
		}																// if not, the neighbor will be added

		std::vector<int> getConnections() {
			std::vector<int> keys;										// will return a vector containing all neighbors
			for (std::map<int, int>::iterator it = connectedTo.begin();	// Use iterator to find all keys
									it != connectedTo.end(); ++it)
				keys.push_back(it->first);								// add to vector
			return keys;												// return vector
		}

		int getId() { return this->id; }								// return this vector's id

		int getWeight(int nbr) { return this->connectedTo[nbr]; }		// get weight of single edge from this vertex to nbr

		friend std::ostream &operator<<(std::ostream &stream, Vertex<T> &vert) {
			std::vector<int> connects = vert.getConnections();			// get all neighbors
			for (unsigned int i = 0; i < connects.size(); i++)			// iterate through neighbors
				stream	<< "( " << vert.id << " , " 					// print this vertex's id
						<< connects[i] << " ) \n";						// print neighbor's id
			return stream;												// return stream
		}

		// ADDED CONTENT
		private:
		// Distance variable for shortest path problem
		int distance = 0; // defaults to 0.
		// Copy constructor and Overloaded assignment operator to avoid problems with 
		// deleted default constructor
		public:
		Vertex(const Vertex& copy)
			: id {copy.id}, connectedTo {copy.connectedTo}, payload {copy.payload} {}

		Vertex& operator=(const Vertex& vertex) {
			id			= vertex.id;
			connectedTo	= vertex.connectedTo;
			payload		= vertex.payload;

			return *this;
		}

		int getDistance()		{ return distance }
		void setDistance(int d)	{ distance = d }
};
#endif