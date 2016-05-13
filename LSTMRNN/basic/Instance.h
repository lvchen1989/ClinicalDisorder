#ifndef _JST_INSTANCE_
#define _JST_INSTANCE_

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "N3L.h"
#include "Metric.h"

using namespace std;

class Instance {
public:
	Instance() {
	}
	~Instance() {
	}

	int size() const {
		return words.size();
	}

	void clear() {
		labels.clear();
		words.clear();
		for (int i = 0; i < size(); i++) {
			sparsefeatures[i].clear();
			charfeatures[i].clear();
			tagfeatures[i].clear();
		}
		sparsefeatures.clear();
		charfeatures.clear();
		tagfeatures.clear();
	}

	void allocate(int length) {
		clear();
		labels.resize(length);
		words.resize(length);
		tagfeatures.resize(length);
		sparsefeatures.resize(length);
		charfeatures.resize(length);
	}

	void copyValuesFrom(const Instance& anInstance) {
		allocate(anInstance.size());
		for (int i = 0; i < anInstance.size(); i++) {
			labels[i] = anInstance.labels[i];
			words[i] = anInstance.words[i];
			for (int j = 0; j < anInstance.sparsefeatures[i].size(); j++) {
				sparsefeatures[i].push_back(anInstance.sparsefeatures[i][j]);
			}
			for (int j = 0; j < anInstance.charfeatures[i].size(); j++) {
				charfeatures[i].push_back(anInstance.charfeatures[i][j]);
			}
			for (int j = 0; j < anInstance.tagfeatures[i].size(); j++) {
				tagfeatures[i].push_back(anInstance.tagfeatures[i][j]);
			}
		}

	}

	void assignLabel(const vector<string>& resulted_labels) {
		assert(resulted_labels.size() == words.size());
		labels.clear();
		for (int idx = 0; idx < resulted_labels.size(); idx++) {
			labels.push_back(resulted_labels[idx]);
		}
	}

	void Evaluate(const vector<string>& resulted_labels, Metric& eval) const {
		for (int idx = 0; idx < labels.size(); idx++) {
			if (!validlabels(labels[idx]))
				continue;
			if (resulted_labels[idx].compare(labels[idx]) == 0)
				eval.correct_label_count++;
			eval.overall_label_count++;
		}
	}

	void SegEvaluate(const vector<string>& resulted_labels, Metric& eval) const {
		static int idx, idy, endpos;
		hash_set<string> golds;
		// segmentation should be agree in both layers, usually, the first layer defines segmentation
		idx = 0;
		vector<string> initgoldlabels;
		vector<string> mergegoldlabels;

		while (idx < labels.size()) {
			if (is_start_label(labels[idx])) {
				idy = idx;
				endpos = -1;
				while (idy < labels.size()) {
					if (!is_continue_label(labels[idy], labels[idx], idy - idx)) {
						endpos = idy - 1;
						break;
					}
					endpos = idy;
					idy++;
				}
				stringstream ss;
				ss << "[" << idx << "," << endpos << "]";

				initgoldlabels.push_back(cleanLabel(labels[idx]) + ss.str());
//				std::cout<<cleanLabel(labels[idx]) + ss.str()<<" ";
				idx = endpos;
			}
			idx++;
		}

//		std::cout<<"---"<<" ";
//		std::cout<<initgoldlabels.size()<<" ";

		string word = "";
		if(!initgoldlabels.empty()){
			int p=0;
			for(int i=0;i<initgoldlabels.size()-1;i++){

				word+=initgoldlabels[i].substr(1);
				if(initgoldlabels[i][0]=='C'){
					mergegoldlabels.push_back(word);
					word="";
				}else if(initgoldlabels[i+1][0]=='D'){


				}else{
					mergegoldlabels.push_back(word);
					word="";
				}
			}

			word+=initgoldlabels[initgoldlabels.size()-1].substr(1);
			mergegoldlabels.push_back(word);
			word="";

			for(int k=0;k<mergegoldlabels.size();k++){
				golds.insert(mergegoldlabels[k]);
//				std::cout<<mergegoldlabels[k]<<" ";
			}
		}

		initgoldlabels.clear();
		mergegoldlabels.clear();

		vector<string> initprelabels;
		vector<string> mergeprelabels;

		hash_set<string> preds;
		idx = 0;
		while (idx < resulted_labels.size()) {
			if (is_start_label(resulted_labels[idx])) {
				stringstream ss;
				idy = idx;
				endpos = -1;
				while (idy < resulted_labels.size()) {
					if (!is_continue_label(resulted_labels[idy], resulted_labels[idx], idy - idx)) {
						endpos = idy - 1;
						break;
					}
					endpos = idy;
					idy++;
				}
				ss << "[" << idx << "," << endpos << "]";
				initprelabels.push_back(cleanLabel(resulted_labels[idx]) + ss.str());
//				std::cout<<cleanLabel(resulted_labels[idx]) + ss.str()<<" ";
				idx = endpos;
			}
			idx++;
		}
//		std::cout<<"---"<<" ";

//		std::cout<<initprelabels.size()<<" ";

		word = "";

		if(!initprelabels.empty()){
			int j=0;
			for(int i=0;i<initprelabels.size()-1;i++){
				word+=initprelabels[i].substr(1);
				if(initprelabels[i][0]=='C'){
					mergeprelabels.push_back(word);
					word="";

				}else if(initprelabels[i+1][0]=='D'){

				}else{
					mergeprelabels.push_back(word);
					word="";

				}
			}

			word+=initprelabels[initprelabels.size()-1].substr(1);
			mergeprelabels.push_back(word);
			word="";

			for(int k=0;k<mergeprelabels.size();k++){
				preds.insert(mergeprelabels[k]);
//				std::cout<<mergeprelabels[k]<<" ";
			}
		}
//		std::cout<<""<<std::endl;

		initprelabels.clear();
		mergeprelabels.clear();


		hash_set<string>::iterator iter;
		eval.overall_label_count += golds.size();
		eval.predicated_label_count += preds.size();
		for (iter = preds.begin(); iter != preds.end(); iter++) {
			if (golds.find(*iter) != golds.end()) {
				eval.correct_label_count++;
			}
		}

		hash_set<string>::iterator iter1;

		for (iter = preds.begin(); iter != preds.end(); iter++) {
			bool tag = false;
			for (iter1 = golds.begin(); iter1 != golds.end(); iter1++) {
				if(is_overlap(*iter,*iter1)){
					tag = true;
					break;

				}

			}

			if(tag){
				eval.relax_correct_label_count++;
			}else{
				eval.predicated_falselabel_count++;
			}
		}

		for (iter = golds.begin(); iter != golds.end(); iter++) {
			bool tag = false;
			for (iter1 = preds.begin(); iter1 != preds.end(); iter1++) {
				if(is_overlap(*iter,*iter1)){
					tag = true;
					break;

				}

			}

			if(!tag){
				eval.missgold_label_count++;
			}
		}

	}



public:
	vector<string> labels;
	vector<string> words;
	vector<vector<string> > tagfeatures;
	vector<vector<string> > sparsefeatures;
	vector<vector<string> > charfeatures;

};

#endif

