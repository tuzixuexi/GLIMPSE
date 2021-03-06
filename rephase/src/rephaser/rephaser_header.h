/*******************************************************************************
 * Copyright (C) 2020 Olivier Delaneau, University of Lausanne
 * Copyright (C) 2020 Simone Rubinacci, University of Lausanne
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#ifndef _REPHASER_H
#define _REPHASER_H

#include <utils/otools.h>
#include <objects/hmm_parameters.h>

#include <containers/haplotype_set.h>
#include <containers/variant_map.h>

#include <models/rephase_hmm.h>

class rephaser {
public:
	//COMMAND LINE OPTIONS
	bpo::options_description descriptions;
	bpo::variables_map options;

	//INTERNAL DATA
	haplotype_set H;
	variant_map V;
	hmm_parameters M;

	//MULTI-THREADING
	int i_workers, i_jobs;
	vector < pthread_t > id_workers;
	pthread_mutex_t mutex_workers;

	//COMPUTE DATA
	basic_stats statH;
	vector < rephase_hmm * > HMM;

	//CONSTRUCTOR
	rephaser();
	~rephaser();

	//METHODS
	void rephase_individual(int, int);
	void rephase_iteration();
	void rephase_loop();

	//PARAMETERS
	void declare_options();
	void parse_command_line(vector < string > &);
	void check_options();
	void verbose_options();
	void verbose_files();

	//FILE I/O
	void read_files_and_initialise();
	void rephase(vector < string > &);
	void write_files_and_finalise();
};


#endif


