#include <vs/base/util/FindPath.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace cont;

int findShortestPath(const Matrix<int> &matrix,
					 int startPoint, int endPoint, stack<int> &waypoints)
{
	assert (startPoint >= 0 && endPoint >= 0);
	assert (startPoint < matrix.numColumns() && endPoint < matrix.numColumns());

    if (startPoint == endPoint)
        return 0;   // suche unnötig

	vector<int> way;        // kuerzeste wege zu zielen merken
	vector<int> precursor;  // vorgaenger knoten merken
	queue<int> newNodes;    // zu bearbeitende knoten einreihen
	set <int>
	knownNodes;   // schon besuchte knoten merken

	// start punkt als erste aufgabe definieren
	newNodes.push(startPoint);

	// verhindern das vom ziel punkt aus geprüft wird
	knownNodes.insert(endPoint);

	// initialisieren
	for (int i = 0; i < matrix.numColumns(); i++)
	{
		way.push_back( -1);
		precursor.push_back( -1);
	}

	int from;

	// solange noch knoten fuer nachbarsuche vorhanden sind
	while (!newNodes.empty())
	{
		// den naechsten knoten "from" aus der queue holen
		from = newNodes.front();
		newNodes.pop();

		// falls knoten schon behandelt wurde, nächster knoten
		if (knownNodes.count(from) > 0)
			continue;

		// alle zielknoten "to" durchlaufen
		for (int to = 0; to < matrix.numColumns(); to++)
		{
			// start = ziel unnötig
			if (from == to)
				continue;

			// unpassierbare wege nicht erlauben
			if (matrix.get(from, to) == -1)
				continue;

			// ist weg zum ziel kuerzer als bisher, oder noch gar nicht besucht
			// dann eintragen!
			if (way[from] + matrix.get(from, to) < way[to] || way[to] == -1)
			{
				//  kandidat fuer naechste suche hinzufuegen
				if (knownNodes.count(to) == 0 && from != endPoint)
					newNodes.push(to);

				// knoten als besucht merken
				knownNodes.insert(from);

				// laenge von "from" "to" aus adjazenz matrix holen
				int length = way[from] + matrix.get(from, to);

				// neue laenge weg zum ziel setzen
				way[to] = length;

				// sonderfall: falls die kante from -> to das gewicht 0 hatte...
				if (way[to] == -1)
					way[to] = 0;

				// vorgaenger jeweils merken (baum baut sich von der wurzel
				// her auf) fuer waypoints spaeter
				precursor[to] = from;
			}
		}
	}

	// falls ziel nicht erreicht werden konnte -1 zurueck geben
	if (precursor[endPoint] == -1)
		return -1;

	// waypoints von start bis ziel zurueck geben
	waypoints.push(endPoint);

	while (waypoints.top() != startPoint)
		waypoints.push( precursor[waypoints.top()] );

	// start punkt weg nehmen (man ist bereits am start punkt)
	waypoints.pop();

	return way[endPoint];
}


} // util
} // base
} // vs

