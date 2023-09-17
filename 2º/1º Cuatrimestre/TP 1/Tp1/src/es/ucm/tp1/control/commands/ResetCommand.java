package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;

import java.lang.Integer;

public class ResetCommand extends Command {

	private static final String NAME = "reset";

	private static final String DETAILS = "[r]eset [<level> <seed>]";

	private static final String SHORTCUT = "r";

	private static final String HELP = "reset game";

	public ResetCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		game.reset(seed, level);
		
		return true;
	}
	
	private long seed;
	private String level;
	
	protected Command parse(String[] words) throws CommandParseException{
		if (matchCommandName(words[0])) {
			if (words.length < 1 || words.length > 3 || words.length == 2) {
				throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, INCORRECT_NUMBER_OF_ARGS_MSG));
			} else {
				
				if(words.length == 1) {
					
					this.seed = 0;
					this.level = null;
				}
				else {
					
					this.level = words[1];
					
					if(!this.level.equals("easy") && !this.level.equals("test") && 
							!this.level.equals("hard") && !this.level.equals("advanced"))
						throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, "Level must be one of: TEST, EASY, HARD, ADVANCED"));
					
					try {
						
						this.seed = Integer.parseInt(words[2]);
					}
					catch (NumberFormatException e){
						
						throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, "the seed is not a proper long number"));
					}
				}
				
				return this;
			}
		}
		return null;
	}

}