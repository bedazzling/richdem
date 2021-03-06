  m.def("rdFillDepressions",     &Zhou2016<float>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<float>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<float>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<float, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<float, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<float>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<float>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<float>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<float>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<float>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<float>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<float>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<float>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<float,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<float,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<float,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<float,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<float,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<float,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<float,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<float,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<float>>(m, "Array2D_float", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<float>::xy_t,Array2D<float>::xy_t,float>())
      .def(py::init<const Array2D<float>&, float>())
      .def(py::init<const Array2D<double>&, float>())
      .def(py::init<const Array2D<int8_t>&, float>())
      .def(py::init<const Array2D<int16_t>&, float>())
      .def(py::init<const Array2D<int32_t>&, float>())
      .def(py::init<const Array2D<int64_t>&, float>())
      .def(py::init<const Array2D<uint8_t>&, float>())
      .def(py::init<const Array2D<uint16_t>&, float>())
      .def(py::init<const Array2D<uint32_t>&, float>())
      .def(py::init<const Array2D<uint64_t>&, float>())
      .def(py::init<float*, const int, const int>())
      .def("size",      &Array2D<float>::size)
      .def("width",     &Array2D<float>::width)
      .def("height",    &Array2D<float>::height)
      .def("empty",     &Array2D<float>::empty)
      .def("noData",    &Array2D<float>::noData)
      .def("min",       &Array2D<float>::min)
      .def("max",       &Array2D<float>::max)
      .def("setNoData", [](Array2D<float> &a, const float ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const double ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const int8_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const int16_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const int32_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const int64_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const uint8_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const uint16_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const uint32_t ndval){ a.setNoData((float)ndval); })
      .def("setNoData", [](Array2D<float> &a, const uint64_t ndval){ a.setNoData((float)ndval); })
      .def_readwrite("geotransform", &Array2D<float>::geotransform)
      .def_readwrite("projection",   &Array2D<float>::projection)
      .def_readwrite("metadata",     &Array2D<float>::metadata)
      .def("copy", [](const Array2D<float> a){
        return a;
      })
      .def("fromArray", [](Array2D<float> &a, py::handle src){
        // if(!py::array_t<float>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<float, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        float* dat = (float*)buf.data();
        for(Array2D<float>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<float> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(float),
          py::format_descriptor<float>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(float) * arr.width(), sizeof(float)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<float> &a) {
            return "<RichDEM array: type=float, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<float> &a, const int x, const int y) -> float& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<float> &a, const int i) -> float& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<double>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<double>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<double>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<double, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<double, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<double>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<double>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<double>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<double>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<double>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<double>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<double>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<double>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<double,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<double,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<double,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<double,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<double,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<double,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<double,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<double,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<double>>(m, "Array2D_double", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<double>::xy_t,Array2D<double>::xy_t,double>())
      .def(py::init<const Array2D<float>&, double>())
      .def(py::init<const Array2D<double>&, double>())
      .def(py::init<const Array2D<int8_t>&, double>())
      .def(py::init<const Array2D<int16_t>&, double>())
      .def(py::init<const Array2D<int32_t>&, double>())
      .def(py::init<const Array2D<int64_t>&, double>())
      .def(py::init<const Array2D<uint8_t>&, double>())
      .def(py::init<const Array2D<uint16_t>&, double>())
      .def(py::init<const Array2D<uint32_t>&, double>())
      .def(py::init<const Array2D<uint64_t>&, double>())
      .def(py::init<double*, const int, const int>())
      .def("size",      &Array2D<double>::size)
      .def("width",     &Array2D<double>::width)
      .def("height",    &Array2D<double>::height)
      .def("empty",     &Array2D<double>::empty)
      .def("noData",    &Array2D<double>::noData)
      .def("min",       &Array2D<double>::min)
      .def("max",       &Array2D<double>::max)
      .def("setNoData", [](Array2D<double> &a, const float ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const double ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const int8_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const int16_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const int32_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const int64_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const uint8_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const uint16_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const uint32_t ndval){ a.setNoData((double)ndval); })
      .def("setNoData", [](Array2D<double> &a, const uint64_t ndval){ a.setNoData((double)ndval); })
      .def_readwrite("geotransform", &Array2D<double>::geotransform)
      .def_readwrite("projection",   &Array2D<double>::projection)
      .def_readwrite("metadata",     &Array2D<double>::metadata)
      .def("copy", [](const Array2D<double> a){
        return a;
      })
      .def("fromArray", [](Array2D<double> &a, py::handle src){
        // if(!py::array_t<double>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<double, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        double* dat = (double*)buf.data();
        for(Array2D<double>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<double> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(double),
          py::format_descriptor<double>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(double) * arr.width(), sizeof(double)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<double> &a) {
            return "<RichDEM array: type=double, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<double> &a, const int x, const int y) -> double& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<double> &a, const int i) -> double& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<int8_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<int8_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<int8_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<int8_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<int8_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<int8_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<int8_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<int8_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<int8_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<int8_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<int8_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<int8_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<int8_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<int8_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<int8_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<int8_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<int8_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<int8_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<int8_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<int8_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<int8_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<int8_t>>(m, "Array2D_int8_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<int8_t>::xy_t,Array2D<int8_t>::xy_t,int8_t>())
      .def(py::init<const Array2D<float>&, int8_t>())
      .def(py::init<const Array2D<double>&, int8_t>())
      .def(py::init<const Array2D<int8_t>&, int8_t>())
      .def(py::init<const Array2D<int16_t>&, int8_t>())
      .def(py::init<const Array2D<int32_t>&, int8_t>())
      .def(py::init<const Array2D<int64_t>&, int8_t>())
      .def(py::init<const Array2D<uint8_t>&, int8_t>())
      .def(py::init<const Array2D<uint16_t>&, int8_t>())
      .def(py::init<const Array2D<uint32_t>&, int8_t>())
      .def(py::init<const Array2D<uint64_t>&, int8_t>())
      .def(py::init<int8_t*, const int, const int>())
      .def("size",      &Array2D<int8_t>::size)
      .def("width",     &Array2D<int8_t>::width)
      .def("height",    &Array2D<int8_t>::height)
      .def("empty",     &Array2D<int8_t>::empty)
      .def("noData",    &Array2D<int8_t>::noData)
      .def("min",       &Array2D<int8_t>::min)
      .def("max",       &Array2D<int8_t>::max)
      .def("setNoData", [](Array2D<int8_t> &a, const float ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const double ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const int8_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const int16_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const int32_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const int64_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const uint8_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const uint16_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const uint32_t ndval){ a.setNoData((int8_t)ndval); })
      .def("setNoData", [](Array2D<int8_t> &a, const uint64_t ndval){ a.setNoData((int8_t)ndval); })
      .def_readwrite("geotransform", &Array2D<int8_t>::geotransform)
      .def_readwrite("projection",   &Array2D<int8_t>::projection)
      .def_readwrite("metadata",     &Array2D<int8_t>::metadata)
      .def("copy", [](const Array2D<int8_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<int8_t> &a, py::handle src){
        // if(!py::array_t<int8_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<int8_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        int8_t* dat = (int8_t*)buf.data();
        for(Array2D<int8_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<int8_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(int8_t),
          py::format_descriptor<int8_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(int8_t) * arr.width(), sizeof(int8_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<int8_t> &a) {
            return "<RichDEM array: type=int8_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<int8_t> &a, const int x, const int y) -> int8_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<int8_t> &a, const int i) -> int8_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<int16_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<int16_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<int16_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<int16_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<int16_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<int16_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<int16_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<int16_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<int16_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<int16_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<int16_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<int16_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<int16_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<int16_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<int16_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<int16_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<int16_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<int16_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<int16_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<int16_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<int16_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<int16_t>>(m, "Array2D_int16_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<int16_t>::xy_t,Array2D<int16_t>::xy_t,int16_t>())
      .def(py::init<const Array2D<float>&, int16_t>())
      .def(py::init<const Array2D<double>&, int16_t>())
      .def(py::init<const Array2D<int8_t>&, int16_t>())
      .def(py::init<const Array2D<int16_t>&, int16_t>())
      .def(py::init<const Array2D<int32_t>&, int16_t>())
      .def(py::init<const Array2D<int64_t>&, int16_t>())
      .def(py::init<const Array2D<uint8_t>&, int16_t>())
      .def(py::init<const Array2D<uint16_t>&, int16_t>())
      .def(py::init<const Array2D<uint32_t>&, int16_t>())
      .def(py::init<const Array2D<uint64_t>&, int16_t>())
      .def(py::init<int16_t*, const int, const int>())
      .def("size",      &Array2D<int16_t>::size)
      .def("width",     &Array2D<int16_t>::width)
      .def("height",    &Array2D<int16_t>::height)
      .def("empty",     &Array2D<int16_t>::empty)
      .def("noData",    &Array2D<int16_t>::noData)
      .def("min",       &Array2D<int16_t>::min)
      .def("max",       &Array2D<int16_t>::max)
      .def("setNoData", [](Array2D<int16_t> &a, const float ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const double ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const int8_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const int16_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const int32_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const int64_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const uint8_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const uint16_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const uint32_t ndval){ a.setNoData((int16_t)ndval); })
      .def("setNoData", [](Array2D<int16_t> &a, const uint64_t ndval){ a.setNoData((int16_t)ndval); })
      .def_readwrite("geotransform", &Array2D<int16_t>::geotransform)
      .def_readwrite("projection",   &Array2D<int16_t>::projection)
      .def_readwrite("metadata",     &Array2D<int16_t>::metadata)
      .def("copy", [](const Array2D<int16_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<int16_t> &a, py::handle src){
        // if(!py::array_t<int16_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<int16_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        int16_t* dat = (int16_t*)buf.data();
        for(Array2D<int16_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<int16_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(int16_t),
          py::format_descriptor<int16_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(int16_t) * arr.width(), sizeof(int16_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<int16_t> &a) {
            return "<RichDEM array: type=int16_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<int16_t> &a, const int x, const int y) -> int16_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<int16_t> &a, const int i) -> int16_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<int32_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<int32_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<int32_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<int32_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<int32_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<int32_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<int32_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<int32_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<int32_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<int32_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<int32_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<int32_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<int32_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<int32_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<int32_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<int32_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<int32_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<int32_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<int32_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<int32_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<int32_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<int32_t>>(m, "Array2D_int32_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<int32_t>::xy_t,Array2D<int32_t>::xy_t,int32_t>())
      .def(py::init<const Array2D<float>&, int32_t>())
      .def(py::init<const Array2D<double>&, int32_t>())
      .def(py::init<const Array2D<int8_t>&, int32_t>())
      .def(py::init<const Array2D<int16_t>&, int32_t>())
      .def(py::init<const Array2D<int32_t>&, int32_t>())
      .def(py::init<const Array2D<int64_t>&, int32_t>())
      .def(py::init<const Array2D<uint8_t>&, int32_t>())
      .def(py::init<const Array2D<uint16_t>&, int32_t>())
      .def(py::init<const Array2D<uint32_t>&, int32_t>())
      .def(py::init<const Array2D<uint64_t>&, int32_t>())
      .def(py::init<int32_t*, const int, const int>())
      .def("size",      &Array2D<int32_t>::size)
      .def("width",     &Array2D<int32_t>::width)
      .def("height",    &Array2D<int32_t>::height)
      .def("empty",     &Array2D<int32_t>::empty)
      .def("noData",    &Array2D<int32_t>::noData)
      .def("min",       &Array2D<int32_t>::min)
      .def("max",       &Array2D<int32_t>::max)
      .def("setNoData", [](Array2D<int32_t> &a, const float ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const double ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const int8_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const int16_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const int32_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const int64_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const uint8_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const uint16_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const uint32_t ndval){ a.setNoData((int32_t)ndval); })
      .def("setNoData", [](Array2D<int32_t> &a, const uint64_t ndval){ a.setNoData((int32_t)ndval); })
      .def_readwrite("geotransform", &Array2D<int32_t>::geotransform)
      .def_readwrite("projection",   &Array2D<int32_t>::projection)
      .def_readwrite("metadata",     &Array2D<int32_t>::metadata)
      .def("copy", [](const Array2D<int32_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<int32_t> &a, py::handle src){
        // if(!py::array_t<int32_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<int32_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        int32_t* dat = (int32_t*)buf.data();
        for(Array2D<int32_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<int32_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(int32_t),
          py::format_descriptor<int32_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(int32_t) * arr.width(), sizeof(int32_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<int32_t> &a) {
            return "<RichDEM array: type=int32_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<int32_t> &a, const int x, const int y) -> int32_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<int32_t> &a, const int i) -> int32_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<int64_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<int64_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<int64_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<int64_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<int64_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<int64_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<int64_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<int64_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<int64_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<int64_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<int64_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<int64_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<int64_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<int64_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<int64_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<int64_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<int64_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<int64_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<int64_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<int64_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<int64_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<int64_t>>(m, "Array2D_int64_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<int64_t>::xy_t,Array2D<int64_t>::xy_t,int64_t>())
      .def(py::init<const Array2D<float>&, int64_t>())
      .def(py::init<const Array2D<double>&, int64_t>())
      .def(py::init<const Array2D<int8_t>&, int64_t>())
      .def(py::init<const Array2D<int16_t>&, int64_t>())
      .def(py::init<const Array2D<int32_t>&, int64_t>())
      .def(py::init<const Array2D<int64_t>&, int64_t>())
      .def(py::init<const Array2D<uint8_t>&, int64_t>())
      .def(py::init<const Array2D<uint16_t>&, int64_t>())
      .def(py::init<const Array2D<uint32_t>&, int64_t>())
      .def(py::init<const Array2D<uint64_t>&, int64_t>())
      .def(py::init<int64_t*, const int, const int>())
      .def("size",      &Array2D<int64_t>::size)
      .def("width",     &Array2D<int64_t>::width)
      .def("height",    &Array2D<int64_t>::height)
      .def("empty",     &Array2D<int64_t>::empty)
      .def("noData",    &Array2D<int64_t>::noData)
      .def("min",       &Array2D<int64_t>::min)
      .def("max",       &Array2D<int64_t>::max)
      .def("setNoData", [](Array2D<int64_t> &a, const float ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const double ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const int8_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const int16_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const int32_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const int64_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const uint8_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const uint16_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const uint32_t ndval){ a.setNoData((int64_t)ndval); })
      .def("setNoData", [](Array2D<int64_t> &a, const uint64_t ndval){ a.setNoData((int64_t)ndval); })
      .def_readwrite("geotransform", &Array2D<int64_t>::geotransform)
      .def_readwrite("projection",   &Array2D<int64_t>::projection)
      .def_readwrite("metadata",     &Array2D<int64_t>::metadata)
      .def("copy", [](const Array2D<int64_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<int64_t> &a, py::handle src){
        // if(!py::array_t<int64_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<int64_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        int64_t* dat = (int64_t*)buf.data();
        for(Array2D<int64_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<int64_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(int64_t),
          py::format_descriptor<int64_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(int64_t) * arr.width(), sizeof(int64_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<int64_t> &a) {
            return "<RichDEM array: type=int64_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<int64_t> &a, const int x, const int y) -> int64_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<int64_t> &a, const int i) -> int64_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<uint8_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<uint8_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<uint8_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<uint8_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<uint8_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<uint8_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<uint8_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<uint8_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<uint8_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<uint8_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<uint8_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<uint8_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<uint8_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<uint8_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<uint8_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<uint8_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<uint8_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<uint8_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<uint8_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<uint8_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<uint8_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<uint8_t>>(m, "Array2D_uint8_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<uint8_t>::xy_t,Array2D<uint8_t>::xy_t,uint8_t>())
      .def(py::init<const Array2D<float>&, uint8_t>())
      .def(py::init<const Array2D<double>&, uint8_t>())
      .def(py::init<const Array2D<int8_t>&, uint8_t>())
      .def(py::init<const Array2D<int16_t>&, uint8_t>())
      .def(py::init<const Array2D<int32_t>&, uint8_t>())
      .def(py::init<const Array2D<int64_t>&, uint8_t>())
      .def(py::init<const Array2D<uint8_t>&, uint8_t>())
      .def(py::init<const Array2D<uint16_t>&, uint8_t>())
      .def(py::init<const Array2D<uint32_t>&, uint8_t>())
      .def(py::init<const Array2D<uint64_t>&, uint8_t>())
      .def(py::init<uint8_t*, const int, const int>())
      .def("size",      &Array2D<uint8_t>::size)
      .def("width",     &Array2D<uint8_t>::width)
      .def("height",    &Array2D<uint8_t>::height)
      .def("empty",     &Array2D<uint8_t>::empty)
      .def("noData",    &Array2D<uint8_t>::noData)
      .def("min",       &Array2D<uint8_t>::min)
      .def("max",       &Array2D<uint8_t>::max)
      .def("setNoData", [](Array2D<uint8_t> &a, const float ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const double ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const int8_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const int16_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const int32_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const int64_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const uint8_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const uint16_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const uint32_t ndval){ a.setNoData((uint8_t)ndval); })
      .def("setNoData", [](Array2D<uint8_t> &a, const uint64_t ndval){ a.setNoData((uint8_t)ndval); })
      .def_readwrite("geotransform", &Array2D<uint8_t>::geotransform)
      .def_readwrite("projection",   &Array2D<uint8_t>::projection)
      .def_readwrite("metadata",     &Array2D<uint8_t>::metadata)
      .def("copy", [](const Array2D<uint8_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<uint8_t> &a, py::handle src){
        // if(!py::array_t<uint8_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<uint8_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        uint8_t* dat = (uint8_t*)buf.data();
        for(Array2D<uint8_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<uint8_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(uint8_t),
          py::format_descriptor<uint8_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(uint8_t) * arr.width(), sizeof(uint8_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<uint8_t> &a) {
            return "<RichDEM array: type=uint8_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<uint8_t> &a, const int x, const int y) -> uint8_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<uint8_t> &a, const int i) -> uint8_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<uint16_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<uint16_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<uint16_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<uint16_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<uint16_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<uint16_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<uint16_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<uint16_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<uint16_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<uint16_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<uint16_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<uint16_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<uint16_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<uint16_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<uint16_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<uint16_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<uint16_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<uint16_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<uint16_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<uint16_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<uint16_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<uint16_t>>(m, "Array2D_uint16_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<uint16_t>::xy_t,Array2D<uint16_t>::xy_t,uint16_t>())
      .def(py::init<const Array2D<float>&, uint16_t>())
      .def(py::init<const Array2D<double>&, uint16_t>())
      .def(py::init<const Array2D<int8_t>&, uint16_t>())
      .def(py::init<const Array2D<int16_t>&, uint16_t>())
      .def(py::init<const Array2D<int32_t>&, uint16_t>())
      .def(py::init<const Array2D<int64_t>&, uint16_t>())
      .def(py::init<const Array2D<uint8_t>&, uint16_t>())
      .def(py::init<const Array2D<uint16_t>&, uint16_t>())
      .def(py::init<const Array2D<uint32_t>&, uint16_t>())
      .def(py::init<const Array2D<uint64_t>&, uint16_t>())
      .def(py::init<uint16_t*, const int, const int>())
      .def("size",      &Array2D<uint16_t>::size)
      .def("width",     &Array2D<uint16_t>::width)
      .def("height",    &Array2D<uint16_t>::height)
      .def("empty",     &Array2D<uint16_t>::empty)
      .def("noData",    &Array2D<uint16_t>::noData)
      .def("min",       &Array2D<uint16_t>::min)
      .def("max",       &Array2D<uint16_t>::max)
      .def("setNoData", [](Array2D<uint16_t> &a, const float ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const double ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const int8_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const int16_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const int32_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const int64_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const uint8_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const uint16_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const uint32_t ndval){ a.setNoData((uint16_t)ndval); })
      .def("setNoData", [](Array2D<uint16_t> &a, const uint64_t ndval){ a.setNoData((uint16_t)ndval); })
      .def_readwrite("geotransform", &Array2D<uint16_t>::geotransform)
      .def_readwrite("projection",   &Array2D<uint16_t>::projection)
      .def_readwrite("metadata",     &Array2D<uint16_t>::metadata)
      .def("copy", [](const Array2D<uint16_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<uint16_t> &a, py::handle src){
        // if(!py::array_t<uint16_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<uint16_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        uint16_t* dat = (uint16_t*)buf.data();
        for(Array2D<uint16_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<uint16_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(uint16_t),
          py::format_descriptor<uint16_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(uint16_t) * arr.width(), sizeof(uint16_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<uint16_t> &a) {
            return "<RichDEM array: type=uint16_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<uint16_t> &a, const int x, const int y) -> uint16_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<uint16_t> &a, const int i) -> uint16_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<uint32_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<uint32_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<uint32_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<uint32_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<uint32_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<uint32_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<uint32_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<uint32_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<uint32_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<uint32_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<uint32_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<uint32_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<uint32_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<uint32_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<uint32_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<uint32_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<uint32_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<uint32_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<uint32_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<uint32_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<uint32_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<uint32_t>>(m, "Array2D_uint32_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<uint32_t>::xy_t,Array2D<uint32_t>::xy_t,uint32_t>())
      .def(py::init<const Array2D<float>&, uint32_t>())
      .def(py::init<const Array2D<double>&, uint32_t>())
      .def(py::init<const Array2D<int8_t>&, uint32_t>())
      .def(py::init<const Array2D<int16_t>&, uint32_t>())
      .def(py::init<const Array2D<int32_t>&, uint32_t>())
      .def(py::init<const Array2D<int64_t>&, uint32_t>())
      .def(py::init<const Array2D<uint8_t>&, uint32_t>())
      .def(py::init<const Array2D<uint16_t>&, uint32_t>())
      .def(py::init<const Array2D<uint32_t>&, uint32_t>())
      .def(py::init<const Array2D<uint64_t>&, uint32_t>())
      .def(py::init<uint32_t*, const int, const int>())
      .def("size",      &Array2D<uint32_t>::size)
      .def("width",     &Array2D<uint32_t>::width)
      .def("height",    &Array2D<uint32_t>::height)
      .def("empty",     &Array2D<uint32_t>::empty)
      .def("noData",    &Array2D<uint32_t>::noData)
      .def("min",       &Array2D<uint32_t>::min)
      .def("max",       &Array2D<uint32_t>::max)
      .def("setNoData", [](Array2D<uint32_t> &a, const float ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const double ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const int8_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const int16_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const int32_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const int64_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const uint8_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const uint16_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const uint32_t ndval){ a.setNoData((uint32_t)ndval); })
      .def("setNoData", [](Array2D<uint32_t> &a, const uint64_t ndval){ a.setNoData((uint32_t)ndval); })
      .def_readwrite("geotransform", &Array2D<uint32_t>::geotransform)
      .def_readwrite("projection",   &Array2D<uint32_t>::projection)
      .def_readwrite("metadata",     &Array2D<uint32_t>::metadata)
      .def("copy", [](const Array2D<uint32_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<uint32_t> &a, py::handle src){
        // if(!py::array_t<uint32_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<uint32_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        uint32_t* dat = (uint32_t*)buf.data();
        for(Array2D<uint32_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<uint32_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(uint32_t),
          py::format_descriptor<uint32_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(uint32_t) * arr.width(), sizeof(uint32_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<uint32_t> &a) {
            return "<RichDEM array: type=uint32_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<uint32_t> &a, const int x, const int y) -> uint32_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<uint32_t> &a, const int i) -> uint32_t& {
          return a(i);
        }
      );        m.def("rdFillDepressions",     &Zhou2016<uint64_t>,                     "@@depressions/Zhou2016pf.hpp:Zhou2016@@"); //TODO
  m.def("rdPFepsilon",           &PriorityFloodEpsilon_Barnes2014<uint64_t>,       "Fill all depressions with epsilon."); //TODO

  m.def("rdBreach",              &Lindsay2016<uint64_t>,                  "TODO");

  m.def("TA_SPI",                &TA_SPI<uint64_t, float, double>,        "TODO");         
  m.def("TA_CTI",                &TA_CTI<uint64_t, float, double>,        "TODO");         
  m.def("TA_slope_riserun",      &TA_slope_riserun<uint64_t>,             "TODO");                   
  m.def("TA_slope_percentage",   &TA_slope_percentage<uint64_t>,          "TODO");                      
  m.def("TA_slope_degrees",      &TA_slope_degrees<uint64_t>,             "TODO");                   
  m.def("TA_slope_radians",      &TA_slope_radians<uint64_t>,             "TODO");                   
  m.def("TA_aspect",             &TA_aspect<uint64_t>,                    "TODO");            
  m.def("TA_curvature",          &TA_curvature<uint64_t>,                 "TODO");               
  m.def("TA_planform_curvature", &TA_planform_curvature<uint64_t>,        "TODO");                        
  m.def("TA_profile_curvature",  &TA_profile_curvature<uint64_t>,         "TODO");                       

  m.def("FA_Tarboton",           &FA_Tarboton<uint64_t,double>,          "TODO");
  m.def("FA_Holmgren",           &FA_Holmgren<uint64_t,double>,          "TODO");
  m.def("FA_Quinn",              &FA_Quinn<uint64_t,double>,             "TODO");
  m.def("FA_Freeman",            &FA_Freeman<uint64_t,double>,           "TODO");
  m.def("FA_FairfieldLeymarie",  &FA_FairfieldLeymarie<uint64_t,double>, "TODO");
  m.def("FA_Rho8",               &FA_Rho8<uint64_t,double>,              "TODO");
  m.def("FA_D8",                 &FA_D8<uint64_t,double>,                "TODO");
  m.def("FA_OCallaghan",         &FA_OCallaghan<uint64_t,double>,        "TODO");

  //TODO
  // m.def(
  //   "WrapNumPy",
  //   [](py::handle src){
  //     if (!py::array_t<T>::check_(src))
  //       throw std::runtime_error("WrapNumPy: Array check failed!");

  //     auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
  //     if (!buf)
  //       throw std::runtime_error("WrapNumPy: Could not generate a buffer!")

  //     auto dims = buf.ndim();
  //     if (dims != 2 )
  //       throw std::runtime_error("WrapNumPy: NumPy array must have 2 dimensions.")

  //     value = rd::Array2D<T>((T*) buf.data(),buf.shape()[1],buf.shape()[0]);

  //     return true;
  //   },
  //   "TODO"
  // );

  py::class_<Array2D<uint64_t>>(m, "Array2D_uint64_t", py::buffer_protocol(), py::dynamic_attr())
      .def(py::init<>())
      .def(py::init<Array2D<uint64_t>::xy_t,Array2D<uint64_t>::xy_t,uint64_t>())
      .def(py::init<const Array2D<float>&, uint64_t>())
      .def(py::init<const Array2D<double>&, uint64_t>())
      .def(py::init<const Array2D<int8_t>&, uint64_t>())
      .def(py::init<const Array2D<int16_t>&, uint64_t>())
      .def(py::init<const Array2D<int32_t>&, uint64_t>())
      .def(py::init<const Array2D<int64_t>&, uint64_t>())
      .def(py::init<const Array2D<uint8_t>&, uint64_t>())
      .def(py::init<const Array2D<uint16_t>&, uint64_t>())
      .def(py::init<const Array2D<uint32_t>&, uint64_t>())
      .def(py::init<const Array2D<uint64_t>&, uint64_t>())
      .def(py::init<uint64_t*, const int, const int>())
      .def("size",      &Array2D<uint64_t>::size)
      .def("width",     &Array2D<uint64_t>::width)
      .def("height",    &Array2D<uint64_t>::height)
      .def("empty",     &Array2D<uint64_t>::empty)
      .def("noData",    &Array2D<uint64_t>::noData)
      .def("min",       &Array2D<uint64_t>::min)
      .def("max",       &Array2D<uint64_t>::max)
      .def("setNoData", [](Array2D<uint64_t> &a, const float ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const double ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const int8_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const int16_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const int32_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const int64_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const uint8_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const uint16_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const uint32_t ndval){ a.setNoData((uint64_t)ndval); })
      .def("setNoData", [](Array2D<uint64_t> &a, const uint64_t ndval){ a.setNoData((uint64_t)ndval); })
      .def_readwrite("geotransform", &Array2D<uint64_t>::geotransform)
      .def_readwrite("projection",   &Array2D<uint64_t>::projection)
      .def_readwrite("metadata",     &Array2D<uint64_t>::metadata)
      .def("copy", [](const Array2D<uint64_t> a){
        return a;
      })
      .def("fromArray", [](Array2D<uint64_t> &a, py::handle src){
        // if(!py::array_t<uint64_t>::check_(src)) //TODO: What's this about?
          // return false;

        auto buf = py::array_t<uint64_t, py::array::c_style | py::array::forcecast>::ensure(src);
        if (!buf)
          throw std::runtime_error("Unable to convert array to RichDEM object!");

        auto dims = buf.ndim();
        if (dims != 2 )
          throw std::runtime_error("Array must have two dimensions!");

        a.clear();
        a.resize(buf.shape()[1], buf.shape()[0]);
        uint64_t* dat = (uint64_t*)buf.data();
        for(Array2D<uint64_t>::i_t i=0;i<a.size();i++)
          a(i) = dat[i];
      })
      .def_buffer([](Array2D<uint64_t> &arr) -> py::buffer_info {
        return py::buffer_info(
          arr.getData(),
          sizeof(uint64_t),
          py::format_descriptor<uint64_t>::format(),
          2,                                           //Dimensions
          {arr.height(), arr.width()},                 //Shape
          {sizeof(uint64_t) * arr.width(), sizeof(uint64_t)} //Stride (in bytes)
        );
      })
      .def("__repr__",
        [](const Array2D<uint64_t> &a) {
            return "<RichDEM array: type=uint64_t, width="+std::to_string(a.width())+", height="+std::to_string(a.height())+", owned="+std::to_string(a.owned())+">";
        }
      )
      .def("__call__",
        [](Array2D<uint64_t> &a, const int x, const int y) -> uint64_t& {
          return a(x,y);
        }
      )
      .def("__call__",
        [](Array2D<uint64_t> &a, const int i) -> uint64_t& {
          return a(i);
        }
      );      