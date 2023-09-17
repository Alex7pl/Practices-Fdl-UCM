package es.ucm.tp1.control.commands;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;

public class DumpCommand extends Command{
	
	private static final String NAME = "dump";

	private static final String DETAILS = "[d]ump <filename>";

	private static final String SHORTCUT = "d";

	private static final String HELP = "Shows the content of a saved file";

	private static final String FAILED_MSG = "An error ocurred on reading a file";

	public DumpCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {

		try {
			
			System.out.println(print());
		}
		catch(IOException e) {
			
			System.out.println(e.getMessage());
			
			throw new CommandExecuteException(FAILED_MSG);
		}
		
		return false;
	}
	
	private String fileName;
	
	private String print() throws IOException{
		
		fileName = fileName + ".txt";
		
		Scanner in = null;
		StringBuilder buffer = new StringBuilder();
		
		try {
			
			in = new Scanner(new BufferedReader(new FileReader(fileName)));
			
			while(in.hasNext()) buffer.append(in.nextLine()).append("\n");
		}
		finally {
			
			if(in != null )in.close();
		}
		
		return buffer.toString();
	}
	
	protected Command parse(String[] words) throws CommandParseException{
		
		if (matchCommandName(words[0])) {
			
			if (words.length != 2) {
				throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, INCORRECT_NUMBER_OF_ARGS_MSG));
			} else {
				
				fileName = words[1];
				return this;
			}
		}
		
		return null;
		
	}
	
}
