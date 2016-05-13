/*
 * Metric.h
 *
 *  Created on: Mar 17, 2015
 *      Author: mszhang
 */

#ifndef SRC_METRIC_H_
#define SRC_METRIC_H_
#include "IO.h"

using namespace std;

class Metric {

public:
  int overall_label_count;
  int correct_label_count;
  int predicated_label_count;
  int relax_correct_label_count;
  int predicated_falselabel_count;
  int missgold_label_count;
public:
  Metric()
  {
    overall_label_count = 0;
    correct_label_count = 0;
    predicated_label_count = 0;
    relax_correct_label_count=0;
    predicated_falselabel_count = 0;
    missgold_label_count = 0;
  }

  ~Metric(){}

  void reset()
  {
    overall_label_count = 0;
    correct_label_count = 0;
    predicated_label_count = 0;
    relax_correct_label_count=0;
    predicated_falselabel_count = 0;
    missgold_label_count = 0;
  }

  bool bIdentical()
  {
    if(predicated_label_count == 0)
    {
      if(overall_label_count == correct_label_count)
      {
        return true;
      }
      return false;
    }
    else
    {
      if(overall_label_count == correct_label_count && predicated_label_count == correct_label_count)
      {
        return true;
      }
      return false;
    }
  }

  double getAccuracy()
  {
    if(predicated_label_count == 0)
    {
      return correct_label_count*1.0/overall_label_count;
    }
    else
    {
      return correct_label_count*2.0/(overall_label_count + predicated_label_count);
    }
  }

  double getRelaxAccuracy()
  {
    if(predicated_label_count == 0)
    {
      return relax_correct_label_count*1.0/(relax_correct_label_count+predicated_falselabel_count);
    }
    else
    {
      return relax_correct_label_count*2.0/(relax_correct_label_count*2.0 + missgold_label_count+predicated_falselabel_count);
    }
  }

  void print()
  {
    if(predicated_label_count == 0)
    {
      std::cout << "Accuracy:\tP=" << correct_label_count << "/" << overall_label_count
          << "=" << correct_label_count*1.0/overall_label_count << std::endl;
    }
    else
    {
      std::cout << "Recall:\tP=" << correct_label_count << "/" << overall_label_count << "=" << correct_label_count*1.0/overall_label_count
        << ", " << "Accuracy:\tP=" << correct_label_count << "/" << predicated_label_count << "=" << correct_label_count*1.0/predicated_label_count
        << ", " << "Fmeasure:\t" << correct_label_count*2.0/(overall_label_count + predicated_label_count) << std::endl;

      std::cout << "Relax Recall:\tP=" << relax_correct_label_count << "/" << relax_correct_label_count+missgold_label_count << "=" << relax_correct_label_count*1.0/(relax_correct_label_count+missgold_label_count)
        << ", " << "Relax Accuracy:\tP=" << relax_correct_label_count << "/" << relax_correct_label_count+predicated_falselabel_count << "=" << relax_correct_label_count*1.0/(relax_correct_label_count+predicated_falselabel_count)
        << ", " << "Relax Fmeasure:\t" << relax_correct_label_count*2.0/(relax_correct_label_count*2.0 + missgold_label_count+predicated_falselabel_count) << std::endl;

    }
  }

  void loadModel(LStream &inf) {
    ReadBinary(inf, overall_label_count);
    ReadBinary(inf, correct_label_count);
    ReadBinary(inf, predicated_label_count);
    ReadBinary(inf, relax_correct_label_count);
    ReadBinary(inf, predicated_falselabel_count);
    ReadBinary(inf, missgold_label_count);
    // cout << overall_label_count << correct_label_count << predicated_label_count <<endl;

  }
  void writeModel(LStream &outf) {
    WriteBinary(outf, overall_label_count);
    WriteBinary(outf, correct_label_count);
    WriteBinary(outf, predicated_label_count);
    WriteBinary(outf, relax_correct_label_count);
    WriteBinary(outf, predicated_falselabel_count);
    WriteBinary(outf, missgold_label_count);
    // cout << overall_label_count << correct_label_count << predicated_label_count <<endl;
  }
};

#endif /* SRC_EXAMPLE_H_ */
