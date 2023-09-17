package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;

import java.lang.Integer;

public class CheatCommand extends Command{
	
	
	private static final String NAME = "cheat";

	private static final String DETAILS = "Cheat [1..5]";

	private static final String SHORTCUT = "[1...5]";

	private static final String HELP = "Removes all elements of last visible column, and adds an Advanced Object";
	
	
	public CheatCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}


	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		game.cheat(this.id);
		
		return true;
	}
	
	private int id;
	
	protected Command parse(String[] words) throws CommandParseException{
		if (words[0].equals("1") || words[0].equals("2") || words[0].equals("3") ||
				words[0].equals("4") || words[0].equals("5")) {
			if (words.length != 1) {
				throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, INCORRECT_NUMBER_OF_ARGS_MSG));
			} else {
				
				this.id = Integer.parseInt(words[0]);
				return this;
			}
		}
		return null;
	}
	
	
	
}
