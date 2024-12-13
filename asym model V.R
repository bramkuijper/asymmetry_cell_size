#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#asym model V: multivariate
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

set.seed(123)
rm(list = ls())

# Cell birth function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#creates a new cell list with inherited components, asymmetry traits reaction norms (alpha (total asymmetry) and v (normalised inheirtance ratio eigevector)
#with mutations 
#division time function (inheritance function and mother asymmetry cost function)
#places in simulation time


create_cell <- function(b1, b2,alpha_m, alpha_int, alpha_grad,v_int, v_grad, mu, birth) {
  cell <- list()
  
  #bi: heritable components 
  cell$b1 <- b1 
  cell$b2 <- b2 
  
  cell$alpha_m <- alpha_m
  
  #alpha and v: asymmetry traits inheritance with mutation 
  # a reaction norm with b1: intercept + gradient
  cell$alpha_int <- alpha_int + rnorm(1, mean = 0, sd = mu)
  cell$alpha_grad <- alpha_grad + rnorm(1, mean = 0, sd = mu)
  cell$alpha <- cell$alpha_int + cell$alpha_grad * cell$b1

  cell$v_int <- v_int + rnorm(1, mean = 0, sd = mu)
  cell$v_grad <- v_grad + rnorm(1, mean = 0, sd = mu)
  cell$v <- cell$v_int + cell$v_grad * cell$b1
  
 
  # inverse of division rate function + asym cost function
  cell$divT <- 1 / (3 * cell$b1^2 - (1/3) * cell$b1^3 - 2 * cell$b2^2 + 4 * cell$b1 * cell$b2 + 100 - (1/20) * cell$alpha_m^3) #division asymmetry
  cell$birth <- birth  #simulation time of birth 
  cell$division <- birth + cell$divT  #simulation time of division
  
  return(cell)}

# Cell division function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#Divides cell into higher and lower daughter cells according to 
#inheritance, component accumulation (fixed) and asymmetry traits  
#bounding of inheritance



divide <- function(cell, u1, u2, mu) {
  
  
  # Calculate the symmetrical division after accumulation

  b1s <- (cell$b1 + u1) / 2
  b2s <- (cell$b2 + u2) / 2
  
  # Calculate total asymmetry magnitude using alpha and reaction norm with b1s
  alpha <- cell$alpha_int + cell$alpha_grad * b1s
  
  # Calculate direction vector v using reaction norm with b1s
  v <- cell$v_int + cell$v_grad * b1s
  v1_norm <- v / (v + 1)
  v2_norm <- 1 / (v + 1)
  
  # Calculate asymmetry in each component
  a1 <- alpha * v1_norm
  a2 <- alpha * v2_norm
  
  # Apply bounds to asymmetry values
  a1 <- pmin(pmax(a1, 0), b1s) #inheritance of b1 within asymmetry bounds
  a2 <- pmin(pmax(a2, 0), b2s)
  
  #higher cell
  h_cell <- create_cell(
    b1 = b1s + a1,
    b2 = b2s + a2,
    alpha_m = a1+a2,
    alpha_int = cell$alpha_int,
    alpha_grad = cell$alpha_grad,
    v_int = cell$v_int,
    v_grad = cell$v_grad,
    mu = mu,
    birth = cell$birth + cell$divT)
  
  
  #lower cell
  l_cell <- create_cell(
    b1 = b1s - a1,
    b2 = b2s - a2,
    alpha_m = a1+a2,
    alpha_int = cell$alpha_int,
    alpha_grad = cell$alpha_grad,
    v_int = cell$v_int,
    v_grad = cell$v_grad,
    mu = mu,
    birth = cell$birth + cell$divT)
  

  return(list(h_cell, l_cell))}

# Simulation function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#creates initial cell
#recording simulation data 
#selection events
#timing of division, selection, recording and simulation end 


simulate <- function(sim_length, recording, limit, mu,alpha_m_initial, 
                     b1_initial, u1, alpha_int_initial, alpha_grad_initial,
                     b2_initial, u2, v_int_initial, v_grad_initial) {
  
  # Create the initial cell at time = 0
  cells <- list(create_cell(
    b1 = b1_initial,
    b2 = b2_initial,
    alpha_m = alpha_m_initial,
    alpha_int = alpha_int_initial,
    alpha_grad = alpha_grad_initial,
    v_int = v_int_initial,
    v_grad = v_grad_initial,
    mu = mu,
    birth = 0))
  
  # Create a data frame to record the number of cells at each time step
  cell_count <- data.frame(
    sim_t = numeric(),
    count = numeric(),
    avg_alpha_int = numeric(),
    avg_alpha_grad = numeric(),
    avg_v_int = numeric(),
    avg_v_grad = numeric(),
    avg_b1 = numeric(),
    avg_b2 = numeric())
  
  # Start next recording time
  next_recording <- recording
  
  while (TRUE) {
    
    # Apply selection if over limit
    if (length(cells) > limit) {
      cells <- cells[-sample(length(cells), 1)]  # Remove one cell
    }
    
    # Find next cell to divide
    cell_next_index <- which.min(sapply(cells, function(cell) cell$division))
    cell_next <- cells[[cell_next_index]]
    
    # Ending simulation
    if (cell_next$division > sim_length) {
      break
    }
    
    # Recording cell numbers and traits
    if (cell_next$division >= next_recording) {
      
      # Compute averages of the traits
      avg_alpha_int <- mean(sapply(cells, function(cell) cell$alpha_int))
      avg_alpha_grad <- mean(sapply(cells, function(cell) cell$alpha_grad))
      avg_v_int <- mean(sapply(cells, function(cell) cell$v_int))
      avg_v_grad <- mean(sapply(cells, function(cell) cell$v_grad))
      avg_b1 <- mean(sapply(cells, function(cell) cell$b1))
      avg_b2 <- mean(sapply(cells, function(cell) cell$b2))
      
      # Record data into the cell_count data frame
      cell_count <- rbind(cell_count, data.frame(
        sim_t = next_recording,
        count = length(cells),
        avg_alpha_int = avg_alpha_int,
        avg_alpha_grad = avg_alpha_grad,
        avg_v_int = avg_v_int,
        avg_v_grad = avg_v_grad,
        avg_b1 = avg_b1,
        avg_b2 = avg_b2))
      
      print(tail(cell_count, 1))
      
      
      next_recording <- next_recording + recording
    }
    
    # Remove dividing cell
    cells <- cells[-cell_next_index]
    
    # Dividing cell
    new_cells <- divide(cell_next, u1, u2, mu)
    
    # Adding new cells
    cells <- c(cells, new_cells)
  }
  
  # Storing final cell population in a data frame
  cell_population <- do.call(rbind, lapply(cells, function(cell) data.frame(
    b1 = cell$b1,
    b2 = cell$b2,
    alpha_int = cell$alpha_int,
    alpha_grad = cell$alpha_grad,
    v_int = cell$v_int,
    v_grad = cell$v_grad,
    divT = cell$divT,
    birth = cell$birth,
    division = cell$division)))
  
  return(list(cell_population = cell_population, cell_count = cell_count))
}


# Running ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

sim <- simulate(sim_length = 0.5, recording = 0.005, limit=2000, mu=0.01, alpha_m_initial = 0,
                b1_initial = 2, u1 = 2, b2_initial =2, u2 = 2,
                alpha_int_initial =37 , alpha_grad_initial = -7.5,
                v_int_initial = 2.4, v_grad_initial = -0.3)




hist(sim$cell_population$divT)
sim$cell_population
