# SportsWatch-Arduino
Arduino code for the Connected Sports Watch app.

## Wiring
<p align="center">
	<img src="screenshots/wiring.png" alt="Wiring Schematic" width="550"/>
</p>

## Data Processing
This project contains contains two python scripts :
* readuino : Reads ECG values from the arduino's serial connection and saves them in a csv file.

<p align="center">
	<img src="screenshots/csv.png" alt="CSV file" width="200"/>
</p>

* chart : Processes and charts the ECG values stored in a csv file.

<p align="center">
	<img src="screenshots/processed_chart.png" alt="Processed CSV" width="600"/>
</p>
