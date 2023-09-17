package es.ucm.tp1.control.commands;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.view.GameSerializer;

public class SaveCommand extends Command{
	
	private static final String NAME = "save";

	private static final String DETAILS = "sa[v]e <filename>";

	private static final String SHORTCUT = "v";

	private static final String HELP = " Save the state of the game to a file.";

	private static final String FAILED_MSG = "Failed to save";

	public SaveCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		
		this.printer = new GameSerializer(game);
		
		try {
			
			save();
			System.out.println("Game successfully saved in file " + fileName);
			
		}
		catch(IOException e) {
			
			System.out.println(e.getMessage());
			
			throw new CommandExecuteException(String.format("[ERROR]: %s", FAILED_MSG), e);
		}
		
		return false;
	}
	
	private String fileName;
	private GameSerializer printer;
	
	private void save() throws IOException{
		
		fileName = fileName + ".txt";
		
		BufferedWriter out = null;
		
		try {
			out = new BufferedWriter(new FileWriter(fileName));
			
			out.write(printer.toString());
		}
		finally {
			
			out.close();
		}
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
