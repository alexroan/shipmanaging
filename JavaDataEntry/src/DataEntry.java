import java.io.*;
import java.nio.channels.FileLock;
import java.util.Date;

/**
 * 
 * @author alr16
 * Data Entry class takes in data and writes ship files and log file
 */
public class DataEntry {

	private final String logFile = "../log/log.txt";
	private final double MIN_LNG = -6.5;
	private final double MAX_LNG = -4.75;
	private final double MIN_LAT = 51.5;
	private final double MAX_LAT = 52.75;
	
	public DataEntry(){
		
	}
	
	
	/**
	 * 
	 * @return int[] of date and time in the form (hour:min:sec.day/month/year)
	 */
	public String getDate(){
		Date date = new Date();
		
		StringBuilder sb = new StringBuilder();
		
		sb.append(date.getHours()); sb.append(":");
		sb.append(date.getMinutes()); sb.append(":");
		sb.append(date.getSeconds()); sb.append(".");
		
		sb.append(date.getDate()); sb.append("/");
		sb.append(date.getMonth() + 1); sb.append("/");
		sb.append(date.getYear() + 1900); 
		
		
		
		return sb.toString();
	}


	/**
	 * Wrties information to a file. if file == this.logfile then prints to log file
	 * @param data to be written to file
	 * @param file to be written to
	 */
	public void writeToFile(String data, String file){
		
		FileOutputStream out = null;
		
		boolean isLogFile = file.equals(this.logFile);
		
		try {
			out = new FileOutputStream(file, isLogFile);
		} catch (FileNotFoundException e1) {
			System.err.println(file + " was not found");
		}	
		
		FileLock fl = null;
		try {
			fl = out.getChannel().tryLock();
			if(fl != null){
				out.write(data.getBytes());
				fl.release();
				out.close();
			}
			else{
				System.err.println("Another process is already using "+ file);
			}
				
		}catch(IOException e){
			System.err.println("Could not write to "+file);
		}
	}
	
	/**
	 * 
	 * @return this logfile
	 */
	public String getLogFile(){
		return this.logFile;
	}
		
	/**
	 * gets input from the user
	 * @return strings of users input
	 */
	public String[] readInput(){
		String[] strings = new String[5];
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter the ship's data in the format:");
		System.out.println("MMSI, name, position(lat<space>long), direction and speed");
		System.out.println("After each piece of data specified above press enter");
		for(int i=0; i<5; i++){
			try {
				strings[i] = br.readLine();
			} catch (IOException e) {
				System.err.println("Could not read line "+(i+1));
			}
		}
		return strings;
	}
	
	/**
	 * splits the strings
	 * @param string item to be split
	 * @return split item
	 */
	public String[] splitSpaces(String string){
		return string.split("\\s+");
	}
	
	/**
	 * checks if ship is in area
	 * @param lat
	 * @param lng
	 * @return boolean 
	 */
	public boolean isInShippingArea(double lat, double lng){
		return ((lat >= this.MIN_LAT) && (lat <= this.MAX_LAT) 
				&& (lng >= this.MIN_LNG) && (lng <= this.MAX_LNG));
	}
	
	/**
	 * turns a string array into a string
	 * @param array String[]
	 * @return String
	 */
	public String arrayToString(String[] array){
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<array.length; i++){
			sb.append(array[i]);
			sb.append("\n");
		}
		return sb.toString();
	}

	/**
	 * deletes a ship file
	 * @param file
	 * @return
	 */
	public boolean deleteFile(String file){
		File f = new File(file);
		return f.delete();
	}
	
	/**
	 * main algorithm
	 */
	public void runDataEntry(){
		new File("../log").mkdir();
		new File("../ships").mkdir();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		char in = 0;
		String input = null;
		while(in != 'q'){
			System.out.println("Enter q to quit or i to insert info of a ship");
			try {
				input = br.readLine();
				in = input.charAt(0);
			} catch (IOException e) {
				System.err.println("Could not read in input");
			}
			
			if(in == 'q'){
				break;
			}
			else if(in == 'i'){
				String[] array = this.readInput();
				String[] latLng = this.splitSpaces(array[2]);
				if(this.isInShippingArea(Double.parseDouble(latLng[0]), Double.parseDouble(latLng[1]))){
					System.out.println("Adding ship...");
					String date = this.getDate();
					this.writeToFile(this.arrayToString(array) + date, "../ships/" + array[0]);
					this.writeToFile(array[0] + " data has been entered at " + date + " by Java\n", this.logFile);
				}
				else{
					System.err.println("Ship not in area, removing...");
					this.deleteFile("../ships/" + array[0]);
					this.writeToFile(array[0] + " has been deleted/not been entered because it is not in the shipping area at "+ this.getDate() + "\n", this.logFile);
				}
			}
			else{
				System.out.println("Wrong, please follow the instructions correctly this time...");
			}
		}
	}
	
	public static void main(String[] args){
		DataEntry d = new DataEntry();
		d.runDataEntry();
	}
}
