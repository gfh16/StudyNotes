# Garfield++

## Add ROOT to CMakeLists.txt
```cmake

#--- Dependencies---------------------------------------------------------------
if(DEFINED ENV{ROOTSYS})
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
elseif(DEFINED ROOTSYS)
    list(APPEND CMAKE_PREFIX_PATH ${ROOTSYS})
elseif(DEFINED ROOT_CMAKE_DIR)
    list(APPEND CMAKE_PREFIX_PATH ${ROOT_CMAKE_DIR} )
else()
    message(FATAL_ERROR "Please consider to set ROOTSYS or use -DROOTSYS=..."
                        "If still there is a problem, point to the directory which includes FindROOT.cmake using -DROOT_CMAKE_DIR=...")
endif(DEFINED ENV{ROOTSYS})

find_package(ROOT 6.0 REQUIRED COMPONENTS Geom Gdml)
#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
```



## Main Class&Function

### Gas
```c++
MediumMagboltz gas;
ViewMedium mediumView; //plot gas properties
```

### Sensor
- To Set Connect
```c++
Sensor sensor; // To Set Connect
```

### Geometry&Field
- Two Choice
  - ComponentAnalyticField
  - ComponentAnsys123

```c++
ComponentAnalyticField cmp; // Geometry&Field
Sensor sensor; // To Set Connect
sensor.AddComponent(&cmp);
```
- Set Geo&Gas
```c++
GeometrySimple *geo = new GeometrySimple();
SolidBox *box = new SolidBox(0., 0., 0., 4., 1., 4.);
geo->AddSolid(box, gas);
cmp->SetGeometry(geo);
```

- Create conductor
```c++
cmp->AddWire(xc, yc, wd, v, label1);
cmp->AddPlaneY(0.5 , 0., "Window2");
```
- Add to Readout
```c++
cmp->AddReadout(label1);
sensor->SetTimeWindow(0., tStep, nTimeBins);
sensor->NewSignal();
```

- Set Magnetic Field
```c++
cmp->SetMagneticField(MagX, MagY, MagZ);
```

### Track(Primary)

- Choice
  - TrackHeed
  - TrackSrim

- Connect to Sensor
```
TrackHeed track;
track.SetParticle("muon");
track.SetEnergy(170.e9);
track.SetSensor(&sensor);
```

### Drift
- Choice
  - DriftLineRKF
    - Runge-Kutta-Fehlberg integration
  - AvalancheMicroscopic
  - AvalancheMC

- Connect to Sensor
```c++
DriftLineRKF drift;
drift.SetSensor(&sensor);
```

### Get Signal
- Physics
  - `Weighting fields` to get `the currents induced by electron motion`
  $$
  i_w = -q\vec{v}\cdot\frac{\vec{E_w}}{V_w}
  $$

```c++

// For Raw Signal
///// Add Electrode // the type of Component
const std::string label = "readout";
ComponentAnsys123 fm;
sensor.AddComponent(&fm);
    sensor.AddElectrode(&fm, label);
Sensor::SetTimeWindow(const double tmin, const double tstep, const int nbins);
// switch on 
AvalancheMicroscopic aval;
aval.SetSensor(&sensor);
aval.EnableSignalCalculation();



// For Readout electronics
sensor.SetTransferFunction(transfer);


// To run a track;
track.NewTrack(x0, y0, z0, t0, dx, dy, dz);


// To drift each electron produced in the cluster
// Loop over the clusters along the track.
double xc = 0., yc = 0., zc = 0., tc = 0., ec = 0., extra = 0.;
int nc = 0;
while (track.GetCluster(xc, yc, zc, tc, nc, ec, extra)) {
  // Loop over the electrons in the cluster.
  for (int k = 0; k < nc; ++k) {
    double xe = 0., ye = 0., ze = 0., te = 0., ee = 0.;
    double dx = 0., dy = 0., dz = 0.;
    track.GetElectron(k, xe, ye, ze, te, ee, dx, dy, dz);
    drift.DriftElectron(xe, ye, ze, te);
  }
}

// Draw cellView&driftView
if (plotDrift) {
  cD->Clear();
  // cellView.Plot2d();
  cellView.Plot3d();
  constexpr bool twod = true;
  constexpr bool drawaxis = false;
  // driftView.Plot(twod, drawaxis);
  driftView.Plot3d(twod, drawaxis);
}


// Plot the induced current.
ViewSignal signalView;
signalView.SetSensor(&sensor);
signalView.PlotSignal(label);
// get induced current
Sensor::GetSignal(const std::string label, const int bin);
Sensor::GetElectronSignal(const std::string label, const int bin);
Sensor::GetIonSignal(const std::string label, const int bin);


// Also Can ConvoluteSignal: use a transfer function to induced current.
// Apply the transfer function.
sensor.ConvoluteSignal();
sensor.ConvoluteSignals();
int nt = 0;
if (sensor.ComputeThresholdCrossings(-2., "s", nt)){
    signalView.PlotSignal("s");
}

// Also Can Add noise(to do)


//After the signal of a given track is finished, call
sensor.ClearSignal();

app.Run(kTRUE);

```

### More
- AvalancheMicroscopic
```c++
AvalancheMicroscopic* aval = new AvalancheMicroscopic();
aval->SetSensor(sensor);
aval->EnableSignalCalculation();
aval->EnableMagneticField();
aval->AvalancheElectron(x, y, z, t, e, dx, dy, dz);
int ne = 0, ni = 0;
aval->GetAvalancheSize(ne, ni);
```
                        
- AvalancheMC

- TrackSrim