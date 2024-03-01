#include "slime_particle.hpp"

SlimeParticle::SlimeParticle(Grid& grid, Vector2<double> starting_position) : grid(grid)
{
    this->set_position(starting_position);
    this->grid.deposit_chemoattractant_on_position(this->position, this->chemoattachant_deposition_factor);
}

void SlimeParticle::set_position(Vector2<double> position)
{
    if (!this->grid.is_position_in_bounds(this->position))
    {
        throw std::runtime_error("Setting position not in grid.");
    }
    this->position = position;
}

void SlimeParticle::set_direction(Vector2<double> direction)
{
    this->direction = direction.normalized();
}

void SlimeParticle::motor_stage()
{
    Vector2<double> move_vec = this->direction*this->speed;
    
    Vector2<double> new_position = this->grid.cast_ray_in_grid(this->position, move_vec);

    this->set_position(new_position);
    this->grid.deposit_chemoattractant_on_position(this->position, this->chemoattachant_deposition_factor);
}

void SlimeParticle::sensory_stage()
{
    Vector2<double> front_sensor_offset = this->direction*this->speed;
    Vector2<double> left_sensor_offset = (this->direction*this->speed).rotated(left_right_sensor_angle);
    Vector2<double> right_sensor_offset = (this->direction*this->speed).rotated(-left_right_sensor_angle);

    double left_sensor_read_value = this->grid.get_chemoattractant_on_position(this->position + left_sensor_offset);
    double right_sensor_read_value = this->grid.get_chemoattractant_on_position(this->position + right_sensor_offset);
    double front_sensor_read_value = this->grid.get_chemoattractant_on_position(this->position + front_sensor_offset);

    if ((front_sensor_read_value >= left_sensor_read_value) &&
        (front_sensor_read_value >= right_sensor_read_value))
    {
        return;
    }
    else if ((front_sensor_read_value < left_sensor_read_value) &&
             (front_sensor_read_value < right_sensor_read_value))
    {
        int random_number = generate_random_number(0, 1);
        int rotation_degrees = random_number == 0 ? rotation_angle : -rotation_angle;

        this->direction.rotate(rotation_degrees);
    }
    else if (right_sensor_read_value < left_sensor_read_value)
    {
        this->direction.rotate(rotation_angle);
    }
    else if (left_sensor_read_value < right_sensor_read_value)
    {
        this->direction.rotate(-rotation_angle);
    }
    /* Else just stay on the right path. */
}