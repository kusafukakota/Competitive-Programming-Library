struct Time {
  int lim;
  bool start;
  chrono::system_clock::time_point t;
  Time(int lim): lim(lim), start(false){};
  long double operator()(bool output = true) {
    if(!start) {
      t = chrono::system_clock::now();
      start = true;
      return 0;
    }
    auto d = chrono::system_clock::now() - t;
    auto msec = chrono::duration_cast<chrono::milliseconds>(d).count();
    if(output) {
      cerr << "\n-------------------------------\n";
      if(msec <= lim) {
        cerr << "[\033[36mi\033[m] ";
        cerr << "\033[36mExecution Time : " << msec << " ms\033[m\n";
      }
      else {
        cerr << "[\033[33m!\033[m] ";
        cerr << "\033[33mExecution Time : " << msec << " ms\033[m\n";
      }
      cerr << "-------------------------------\n";
    }
    return msec;
  }
} Time(2000);
