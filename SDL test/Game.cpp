#include "Game.h"
#include "GraphNode.h"
#include "NodeEdge.h"
#include "PillItem.h"
#include "GunItem.h"

void Game::start()
{
	auto vertex104 = std::make_shared<GraphNode>(34,  120, graph);
	auto vertex105 = std::make_shared<GraphNode>(136, 117, graph);
	auto vertex106 = std::make_shared<GraphNode>(136,  45, graph);
	auto vertex107 = std::make_shared<GraphNode>(261,  45, graph);
	auto vertex108 = std::make_shared<GraphNode>(261, 114, graph);
	auto vertex109 = std::make_shared<GraphNode>(320, 114, graph);
	auto vertex110 = std::make_shared<GraphNode>(320,  45, graph);
	auto vertex111 = std::make_shared<GraphNode>(437,  42, graph);
	auto vertex112 = std::make_shared<GraphNode>(437, 114, graph);
	auto vertex113 = std::make_shared<GraphNode>(544, 117, graph);
	auto vertex115 = std::make_shared<GraphNode>(544, 170, graph);
	auto vertex116 = std::make_shared<GraphNode>(439, 173, graph);
	auto vertex117 = std::make_shared<GraphNode>(376, 173, graph);
	auto vertex118 = std::make_shared<GraphNode>(376, 114, graph);
	auto vertex119 = std::make_shared<GraphNode>(197, 117, graph);
	auto vertex120 = std::make_shared<GraphNode>(197, 170, graph);
	auto vertex121 = std::make_shared<GraphNode>(258, 173, graph);
	auto vertex122 = std::make_shared<GraphNode>(258, 229, graph);
	auto vertex123 = std::make_shared<GraphNode>(320, 226, graph);
	auto vertex124 = std::make_shared<GraphNode>(320, 173, graph);
	auto vertex125 = std::make_shared<GraphNode>(378, 229, graph);
	auto vertex126 = std::make_shared<GraphNode>(439, 285, graph);
	auto vertex127 = std::make_shared<GraphNode>(381, 285, graph);
	auto vertex128 = std::make_shared<GraphNode>(194, 232, graph);
	auto vertex129 = std::make_shared<GraphNode>(136, 176, graph);
	auto vertex130 = std::make_shared<GraphNode>(34,  176, graph);
	auto vertex131 = std::make_shared<GraphNode>(133, 285, graph);
	auto vertex132 = std::make_shared<GraphNode>(197, 288, graph);
	auto vertex133 = std::make_shared<GraphNode>(200, 346, graph);
	auto vertex134 = std::make_shared<GraphNode>(381, 344, graph);
	auto vertex135 = std::make_shared<GraphNode>(439, 400, graph);
	auto vertex136 = std::make_shared<GraphNode>(544, 400, graph);
	auto vertex137 = std::make_shared<GraphNode>(504, 456, graph);
	auto vertex138 = std::make_shared<GraphNode>(504, 512, graph);
	auto vertex139 = std::make_shared<GraphNode>(439, 512, graph);
	auto vertex140 = std::make_shared<GraphNode>(439, 456, graph);
	auto vertex141 = std::make_shared<GraphNode>(376, 458, graph);
	auto vertex142 = std::make_shared<GraphNode>(320, 400, graph);
	auto vertex143 = std::make_shared<GraphNode>(381, 397, graph);
	auto vertex144 = std::make_shared<GraphNode>(320, 456, graph);
	auto vertex145 = std::make_shared<GraphNode>(261, 402, graph);
	auto vertex146 = std::make_shared<GraphNode>(197, 400, graph);
	auto vertex147 = std::make_shared<GraphNode>(133, 400, graph);
	auto vertex148 = std::make_shared<GraphNode>(34,  400, graph);
	auto vertex149 = std::make_shared<GraphNode>(77,  458, graph);
	auto vertex150 = std::make_shared<GraphNode>(77,  509, graph);
	auto vertex151 = std::make_shared<GraphNode>(138, 506, graph);
	auto vertex152 = std::make_shared<GraphNode>(136, 456, graph);
	auto vertex153 = std::make_shared<GraphNode>(200, 456, graph);
	auto vertex154 = std::make_shared<GraphNode>(200, 512, graph);
	auto vertex155 = std::make_shared<GraphNode>(258, 514, graph);
	auto vertex156 = std::make_shared<GraphNode>(258, 565, graph);
	auto vertex158 = std::make_shared<GraphNode>(34,  512, graph);
	auto vertex159 = std::make_shared<GraphNode>(320, 565, graph);
	auto vertex160 = std::make_shared<GraphNode>(320, 514, graph);
	auto vertex161 = std::make_shared<GraphNode>(378, 512, graph);
	auto vertex163 = std::make_shared<GraphNode>(544, 514, graph);
	auto vertex224 = std::make_shared<GraphNode>(261, 456, graph);
	auto vertex243 = std::make_shared<GraphNode>(34,   82, graph); // Powerpill
	auto vertex244 = std::make_shared<GraphNode>(541,  80, graph); // Powerpill
	auto vertex245 = std::make_shared<GraphNode>(544, 456, graph); // Powerpill
	auto vertex246 = std::make_shared<GraphNode>(34,  456, graph); // Powerpill
	auto vertex103 = std::make_shared<GraphNode>(34,   48, graph); // Spawn spookje
	auto vertex114 = std::make_shared<GraphNode>(541,  45, graph); // Spawn spookje
	auto vertex157 = std::make_shared<GraphNode>(37,  562, graph); // Spawn spookje
	auto vertex162 = std::make_shared<GraphNode>(541, 568, graph); // Spawn spookje
	auto vertex250 = std::make_shared<GraphNode>(290, 345, graph); // Spawn pacman

	vertex243->addItem(std::make_shared<PillItem>());
	vertex244->addItem(std::make_shared<PillItem>());
	vertex245->addItem(std::make_shared<PillItem>());
	vertex246->addItem(std::make_shared<PillItem>());

	/*auto vertex103 = std::make_shared<GraphNode>(34, 48, graph); // Spawn spookje
	auto vertex114 = std::make_shared<GraphNode>(541, 45, graph); // Spawn spookje
	auto vertex157 = std::make_shared<GraphNode>(37, 562, graph); // Spawn spookje
	auto vertex162 = std::make_shared<GraphNode>(541, 568, graph); // Spawn spookje
	auto vertex250 = std::make_shared<GraphNode>(290, 345, graph); // Spawn pacman*/
	
	graph->addNode( vertex104 );
	graph->addNode( vertex105 );
	graph->addNode( vertex106 );
	graph->addNode( vertex107 );
	graph->addNode( vertex108 );
	graph->addNode( vertex109 );
	graph->addNode( vertex110 );
	graph->addNode( vertex111 );
	graph->addNode( vertex112 );
	graph->addNode( vertex113 );
	graph->addNode( vertex115 );
	graph->addNode( vertex116 );
	graph->addNode( vertex117 );
	graph->addNode( vertex118 );
	graph->addNode( vertex119 );
	graph->addNode( vertex120 );
	graph->addNode( vertex121 );
	graph->addNode( vertex122 );
	graph->addNode( vertex123 );
	graph->addNode( vertex124 );
	graph->addNode( vertex125 );
	graph->addNode( vertex126 );
	graph->addNode( vertex127 );
	graph->addNode( vertex128 );
	graph->addNode( vertex129 );
	graph->addNode( vertex130 );
	graph->addNode( vertex131 );
	graph->addNode( vertex132 );
	graph->addNode( vertex133 );
	graph->addNode( vertex134 );
	graph->addNode( vertex135 );
	graph->addNode( vertex136 );
	graph->addNode( vertex137 );
	graph->addNode( vertex138 );
	graph->addNode( vertex139 );
	graph->addNode( vertex140 );
	graph->addNode( vertex141 );
	graph->addNode( vertex142 );
	graph->addNode( vertex143 );
	graph->addNode( vertex144 );
	graph->addNode( vertex145 );
	graph->addNode( vertex146 );
	graph->addNode( vertex147 );
	graph->addNode( vertex148 );
	graph->addNode( vertex149 );
	graph->addNode( vertex150 );
	graph->addNode( vertex151 );
	graph->addNode( vertex152 );
	graph->addNode( vertex153 );
	graph->addNode( vertex154 );
	graph->addNode( vertex155 );
	graph->addNode( vertex156 );
	graph->addNode( vertex158 );
	graph->addNode( vertex159 );
	graph->addNode( vertex160 );
	graph->addNode( vertex161 );
	graph->addNode( vertex163 );
	graph->addNode( vertex224 );
	graph->addNode( vertex243 );
	graph->addNode( vertex244 );
	graph->addNode( vertex245 );
	graph->addNode( vertex246 );
	graph->addNode( vertex103 );
	graph->addNode( vertex114 );
	graph->addNode( vertex157 );
	graph->addNode( vertex162 );
	graph->addNode( vertex250 );

	vertex103->addEdges(vertex106,0);
	vertex106->addEdges(vertex107,0);
	vertex107->addEdges(vertex108,0);
	vertex108->addEdges(vertex119,0);
	vertex119->addEdges(vertex120,0);
	vertex120->addEdges(vertex121,0);
	vertex121->addEdges(vertex122,0);
	vertex122->addEdges(vertex123,0);
	vertex123->addEdges(vertex124,0);
	vertex124->addEdges(vertex117,0);
	vertex117->addEdges(vertex118,0);
	vertex118->addEdges(vertex109,0);
	vertex109->addEdges(vertex108,0);
	vertex109->addEdges(vertex110,0);
	vertex110->addEdges(vertex111,0);
	vertex112->addEdges(vertex111,0);
	vertex114->addEdges(vertex111,0);
	vertex113->addEdges(vertex112,0);
	vertex115->addEdges(vertex113,0);
	vertex112->addEdges(vertex116,0);
	vertex116->addEdges(vertex115,0);
	vertex116->addEdges(vertex126,0);
	vertex126->addEdges(vertex127,0);
	vertex127->addEdges(vertex125,0);
	vertex125->addEdges(vertex123,0);
	vertex122->addEdges(vertex128,0);
	vertex128->addEdges(vertex132,0);
	vertex132->addEdges(vertex131,0);
	vertex131->addEdges(vertex129,0);
	vertex129->addEdges(vertex105,0);
	vertex105->addEdges(vertex106,0);
	vertex105->addEdges(vertex104,0);
	vertex104->addEdges(vertex130,0);
	vertex130->addEdges(vertex129,0);
	vertex131->addEdges(vertex147,0);
	vertex147->addEdges(vertex148,0);
	vertex149->addEdges(vertex150,0);
	vertex150->addEdges(vertex158,0);
	vertex158->addEdges(vertex157,0);
	vertex157->addEdges(vertex156,0);
	vertex156->addEdges(vertex155,0);
	vertex155->addEdges(vertex154,0);
	vertex154->addEdges(vertex153,0);
	vertex153->addEdges(vertex152,0);
	vertex152->addEdges(vertex151,0);
	vertex151->addEdges(vertex150,0);
	vertex152->addEdges(vertex147,0);
	vertex147->addEdges(vertex146,0);
	vertex146->addEdges(vertex133,0);
	vertex133->addEdges(vertex132,0);
	vertex133->addEdges(vertex250,0);
	vertex250->addEdges(vertex134,0);
	vertex134->addEdges(vertex127,0);
	vertex126->addEdges(vertex135,0);
	vertex135->addEdges(vertex136,0);
	vertex135->addEdges(vertex143,0);
	vertex143->addEdges(vertex134,0);
	vertex143->addEdges(vertex142,0);
	vertex142->addEdges(vertex144,0);
	vertex144->addEdges(vertex141,0);
	vertex144->addEdges(vertex224,0);
	vertex224->addEdges(vertex153,0);
	vertex224->addEdges(vertex145,0);
	vertex145->addEdges(vertex146,0);
	vertex141->addEdges(vertex140,0);
	vertex140->addEdges(vertex135,0);
	vertex140->addEdges(vertex139,0);
	vertex139->addEdges(vertex138,0);
	vertex138->addEdges(vertex137,0);
	vertex138->addEdges(vertex163,0);
	vertex163->addEdges(vertex162,0);
	vertex162->addEdges(vertex159,0);
	vertex159->addEdges(vertex160,0);
	vertex160->addEdges(vertex161,0);
	vertex161->addEdges(vertex141,0);
	vertex159->addEdges(vertex156,0);
	vertex105->addEdges(vertex119,0);
	vertex118->addEdges(vertex112,0);
	vertex103->addEdges(vertex243,0);
	vertex243->addEdges(vertex104,0);
	vertex114->addEdges(vertex244,0);
	vertex244->addEdges(vertex113,0);
	vertex148->addEdges(vertex246,0);
	vertex246->addEdges(vertex149,0);
	vertex136->addEdges(vertex245,0);
	vertex245->addEdges(vertex137,0);


	/*eithNode->addItem(std::make_shared<PillItem>()); // pills
	
	secondNode->addObject(cow); // set objects to node
	fifthNode->addObject(hare);*/

	auto nodes = graph->getNodes();
	for (auto node : nodes)
	{
		objects.push_back(node);
	}
}

std::shared_ptr<CowObject> Game::getCow()
{
	return cow;
}

std::shared_ptr<HareObject> Game::getHare()
{
	return hare;
}

std::shared_ptr<SparseGraph> Game::getGraph()
{
	return graph;
}

std::vector<std::shared_ptr<BaseVisitiable>>& Game::gameObjects()
{
	return objects;
}
