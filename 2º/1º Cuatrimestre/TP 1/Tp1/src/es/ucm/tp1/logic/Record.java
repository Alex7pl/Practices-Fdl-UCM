package es.ucm.tp1.logic;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;

import es.ucm.tp1.control.exceptions.InputOutputRecordException;
import es.ucm.tp1.utils.StringUtils;

public class Record {
	
	private String easyR;
	
	private String hardR;
	
	private String advancedR;
	
	private long record;
	
	
	public Record() {
		
		this.record = 999999999;
		
		hardR = "HARD:99999999" + StringUtils.LINE_SEPARATOR;
		easyR = "EASY:99999999" + StringUtils.LINE_SEPARATOR;
		advancedR = "ADVANCED:999999999" + StringUtils.LINE_SEPARATOR;
	}
	
	public long getRecord() {
		
		return this.record;
	}
	
	public void load(Game game) throws InputOutputRecordException{
		
		Scanner in = null;
		
		String str = null;
		
		try {
			
			in = new Scanner(new BufferedReader(new FileReader("record.txt")));
			
			boolean encontrado = false;
			
			while(in.hasNext()) {
				
				str = in.next();
				
				if(str.split(":")[0].equals("EASY")) easyR = str + StringUtils.LINE_SEPARATOR;
				
				if(str.split(":")[0].equals("HARD")) hardR = str + StringUtils.LINE_SEPARATOR;
				
				if(str.split(":")[0].equals("ADVANCED")) advancedR = str + StringUtils.LINE_SEPARATOR;
				
				if(str.split(":")[0].equals(game.getLevelName())) encontrado = true;
				
				if(encontrado) {
					
					try {
					record = Long.parseLong(str.split(":")[1]);
					encontrado = false;
					}
					catch(NumberFormatException e){
						
						System.out.println("Not a proper long on record.txt");
						
						throw new InputOutputRecordException("El juego terminó", e);
					}
				}
			}
			
		}
		catch(FileNotFoundException e) {
			
			System.out.println(e.getMessage());
			
			throw new InputOutputRecordException("El juego terminó", e);
		}
		finally {
			
			if(in != null) in.close();
		} 
		
	}
	
	public void save(Game game) throws InputOutputRecordException {
		
		PrintWriter out = null;
		
		try {
			
			out = new PrintWriter("record.txt");
			
			if(easyR.split(":")[0].equals(game.getLevelName())) easyR = "EASY:" + game.elapsed() + StringUtils.LINE_SEPARATOR;
			
			if(hardR.split(":")[0].equals(game.getLevelName())) hardR = "HARD:" + game.elapsed() + StringUtils.LINE_SEPARATOR;
			
			if(advancedR.split(":")[0].equals(game.getLevelName())) advancedR = "ADVANCED:" + game.elapsed() + StringUtils.LINE_SEPARATOR;
			
			out.write(easyR + hardR + advancedR);
			
		}
		catch(FileNotFoundException e) {
			
			System.out.println(e.getMessage());
			
			throw new InputOutputRecordException("El juego terminó");
		}
		finally {
			
			if(out != null)out.close();
		}
	}
}
