/*****************************************************************************
 *                                                                           *
 *                        <Routing - AStar Algorithm>                        *
 *             Copyright (C) <2018>   <Municoy, M., Salgado, D.>             *
 *                                                                           *
 *   Contact the authors at: mail@martimunicoy.com                           *
 *                           daniel.salgado@e-campus.uab.cat                 *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *****************************************************************************/

// Include libraries
#include "routing.h"
#include "constants.h"
#include "util.h"
#include "graph.h"
#include "reader.h"
#include "binary.h"

// Main function
int main(int argc, char **argv)
{
    ReaderArguments args;
    SetDefaultReaderArgs(&args);
    ParseReaderArgs(argc, argv, &args);
    CheckReaderArgs(&args);

    Node *node;
    unsigned long nnodes, nways, nedges;

    // Read and check map file data
    node = ReadFile(args.input_file, &nnodes, &nways, &nedges);

    // Minimize graph inconsistencies
    if (!args.fast)
        node = GraphEnhancement(node, &nnodes, nways, nedges);

    // Write graph to a binary file
    WriteBin(args.output_file, node, nnodes);
}
